#include "VisualDictionary.h"
#include <iostream>

/*
 * Konstruktor. Inicjalizuje zmienne. Smart pointery nie wymagają jawnej dealokacji
 */
VisualDictionary::VisualDictionary(int sizeOfDictionary, string pathToDatabase)
{
    this->startPath = path(pathToDatabase);
    this->sizeOfDictionary = sizeOfDictionary;
    this->allFeatures = Mat(0, 128, CV_32FC1, Scalar(0));
    this->selectedWords = Mat(0, 128, CV_32FC1, Scalar(0));
    this->keyPointsDetector = SIFT::create();
    this->featureExtractor = SIFT::create();
}

/*
 * Przechodzi przez wszystkie podkatalogi bazy obrazów wyszukując obrazy, pobiera wszystkie cechy i wybiera określoną
 * ilość w celu utorzenia słownika.
 */
void VisualDictionary::constructDictionary()
{
    recursive_directory_iterator dir(this->startPath), end;

    while (dir != end)
    {
        file_status fs = status(dir->path());

        if (!is_directory(fs)) //Pomiń katalogi
        {
            //Załaduj obrazek
            currentImage = imread(dir->path().string(), CV_LOAD_IMAGE_ANYDEPTH);

            //Sprawdź czy się udało
            if (!currentImage.data)
            {
                cout << "Could not open or find the image" << std::endl;
                exit(-1);
            }

            std::cout << dir->path() << std::endl;
            keyPointsDetector->detect(currentImage, keyPoints);
            featureExtractor->compute(currentImage, keyPoints, currentFeatures);
            cout << "Rows: " << currentFeatures.rows << ", columns " << currentFeatures.cols << endl;
            vconcat(currentFeatures, allFeatures, allFeatures); //Dokonkatenuj pobrane cechy
        }
        ++dir;
    }
    chooseWords(); //Wybierz słowa do słownika
}


/*
 * Wybiera podaną liczbę cech jako słowa i dodaje je do slownika
 */
void VisualDictionary::chooseWords()
{
    cout << "Rows: " << allFeatures.rows << ", columns " << allFeatures.cols << endl;

    int wordsLeftToChoose = sizeOfDictionary;
    int sizeOfNumbers = allFeatures.rows;
    int * numbers = new int[sizeOfNumbers];
    int * chosenNumbers = new int[sizeOfDictionary];

    for (int i = 0; i < sizeOfNumbers; ++i)
    {
        numbers[i] = i;
    }

    srand(time(NULL));

    while (wordsLeftToChoose)
    {
        int x = rand() % sizeOfNumbers;
        chosenNumbers[wordsLeftToChoose - 1] = numbers[x];
        numbers[x] = numbers[sizeOfNumbers--];
        wordsLeftToChoose--;
    }


    for (int i = 0; i < sizeOfDictionary; ++i)
    {
        selectedWords.push_back(allFeatures.row(chosenNumbers[i]));
    }

    cout << "Selected words: rows: " << selectedWords.rows << " , columns: " << selectedWords.cols << endl;
    delete numbers;
    delete chosenNumbers;
}

/*
 * Zapisuje słownik do pliku
 */
void VisualDictionary::saveDictionary()
{
    FileStorage fs(this->dictionaryPath, FileStorage::WRITE);
    fs << "Dictionary" << this->selectedWords;
    fs.release();
}

/*
 * Wczytuje słownik z pliku
 */
void VisualDictionary::loadDictionary()
{
    FileStorage fs(this->dictionaryPath, FileStorage::READ);
    fs["Dictionary"] >> this->selectedWords;
    fs.release();
    cout << "Rows: " << this->selectedWords.rows << " , columns: " << this->selectedWords.cols << endl;
}

/*
 * Pobiera konkretne słowo ze słownika
 */
Mat VisualDictionary::getWord(int rowNumber)
{
    return this->selectedWords.row(rowNumber);
}

/*
 * Zwraca rozmiar słownika
 */
int VisualDictionary::getSize()
{
    return this->sizeOfDictionary;
}



