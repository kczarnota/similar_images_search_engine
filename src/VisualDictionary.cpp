#include "VisualDictionary.h"
#include <iostream>

/*
 * Konstruktor. Inicjalizuje zmienne. Smart pointery nie wymagają jawnej dealokacji
 */
VisualDictionary::VisualDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath)
{
    this->startPath = path(pathToDatabase);
    this->sizeOfDictionary = sizeOfDictionary;
    this->allFeatures = Mat(0, 128, CV_32FC1, Scalar(0));
    this->selectedWords = Mat(0, 128, CV_32FC1, Scalar(0));
    this->keyPointsDetector = SIFT::create();
    this->featureExtractor = SIFT::create();
    this->dictionaryPath = dictionaryPath;

    prepareDictionary();
}

/*
 * Przechodzi przez wszystkie podkatalogi bazy obrazów wyszukując obrazy, pobiera wszystkie cechy i wybiera określoną
 * ilość w celu utorzenia słownika.
 */
void VisualDictionary::constructDictionaryRandom()
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

            //std::cout << dir->path() << std::endl;
            keyPointsDetector->detect(currentImage, keyPoints);
            featureExtractor->compute(currentImage, keyPoints, currentFeatures);
            //cout << "Rows: " << currentFeatures.rows << ", columns " << currentFeatures.cols << endl;
            vconcat(currentFeatures, allFeatures, allFeatures); //Dokonkatenuj pobrane cechy
        }
        ++dir;
    }

    //std::cout << allFeatures << std::endl << std::endl;

    chooseWords(); //Wybierz słowa do słownika

    //std::cout << "Choosen words: " << std::endl;
    //std::cout << selectedWords << std::endl << std::endl;
}


/*
 * Wybiera podaną liczbę cech jako słowa i dodaje je do slownika
 */
void VisualDictionary::chooseWords()
{
    cout << " Wszystkie Rows: " << allFeatures.rows << ", wszystkie columns " << allFeatures.cols << endl;

    int wordsLeftToChoose = sizeOfDictionary;
    int sizeOfNumbers = allFeatures.rows;
    int * numbers = new int[sizeOfNumbers]; //tablica zawierająca wszystkie numery rzędów macierzy
    int * chosenNumbers = new int[sizeOfDictionary]; //tablica w której znajdą się wybrane rzędy

    for (int i = 0; i < sizeOfNumbers; ++i)
    {
        numbers[i] = i;
    }

    srand(time(NULL));

    while (wordsLeftToChoose)
    {
        int x = rand() % sizeOfNumbers;
        chosenNumbers[wordsLeftToChoose - 1] = numbers[x]; //wybrany indeks słowa wpisywany na ostatnie miejsce tabeli
        numbers[x] = numbers[sizeOfNumbers - 1]; //pod wybrany indeks przepisuję ostatni z numerów
        sizeOfNumbers--;
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
 * Konstruuje słownik korzystając z metody k-średnich.
 */
void VisualDictionary::constructDictionaryKMeans()
{
    //Wybranie k losowych słów
    this->constructDictionaryRandom();

    bool shouldStop = false;
    Mat *classes = new Mat[this->selectedWords.rows];
    Mat currentClass(1, 128, CV_32FC1, Scalar(0));
    Mat currentFeature(1, 128, CV_32FC1, Scalar(0));
    Mat difference(1, 128, CV_32FC1, Scalar(0));
    Mat average(1, 128, CV_32FC1, Scalar(0));


    while(!shouldStop)
    {
        //Wyzerowanie macierzy
        for(int i = 0; i < this->selectedWords.rows; ++i)
        {
            classes[i] = Mat(0, 128, CV_32FC1, Scalar(0));
        }

        shouldStop = true;

        //Przypisać do najbliższych klas
        for(int i = 0; i < this->allFeatures.rows; ++i) //każdą z cech trzeba przypisać do klasy
        {
            int minSumIndex = 0, minSum = -1;
            this->allFeatures.row(i).copyTo(currentFeature.row(0)); //wybrana cecha
            for(int j = 0; j < this->selectedWords.rows; ++j) //przeglądam wszystkich reprezentantów klas
            {
                int currentSum = 0;
                this->selectedWords.row(j).copyTo(currentClass.row(0)); //wybrana klasa

                absdiff(currentClass, currentFeature, difference);

                for(int k = 0; k < 128; ++k)
                    currentSum += difference.at<float>(0, k);

                if(minSum == -1 || currentSum < minSum)
                {
                    minSum = currentSum;
                    minSumIndex = j;
                }
            }
            classes[minSumIndex].push_back(currentFeature.row(0));
        }

        //Obliczyć średnie i sprawdzić czy nic się nie zmieniło
        for(int i = 0; i < this->selectedWords.rows; ++i) //dla każdej klasy
        {
            for(int j = 0; j < classes[i].rows; ++j) //przechodzę przez wszystkie wiersze i obliczam średnią
            {
                for(int k = 0; k < 128; ++k)
                {
                    average.at<float>(0, k) += classes[i].row(j).at<float>(0, k); //suma wartości
                }
            }

            for(int k = 0; k < 128; ++k)
            {
                average.at<float>(0, k) = (int)average.at<float>(0, k)/classes[i].rows; //wszystkie wartości podzielone przez liczbę cech
            }


            for(int k = 0; k < 128; ++k)
            {
                if(average.at<float>(0, k) != this->selectedWords.row(i).at<float>(0, k))
                {
                    shouldStop = false;
                    average.row(0).copyTo(this->selectedWords.row(i)); //to zastępujemy stare nowym
                    break;
                }
            }

          /*  absdiff(this->selectedWords.row(i), average.row(0), difference); //wyliczenie różnicy

            double differenceSum = 0;
            for(int k = 0; k < 128; ++k)
            {
                differenceSum += difference.at<float>(0, k); //całkowita różnica
            }

            if(differenceSum != 0) //jeżeli średnie słowo wyszło inne niż było
            {
                shouldStop = false;
                average.row(0).copyTo(this->selectedWords.row(i)); //to zastępujemy stare nowym
            }
            */
        }
    }

    delete []classes;
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
    this->sizeOfDictionary = this->selectedWords.rows;
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
    return this->selectedWords.rows;//this->sizeOfDictionary;
}

void VisualDictionary::testDictionary()
{
    float data1[2][128];
    float data2[3][128];

    int i, j;
    float a = 0;
    for(i = 0; i < 2; ++i)
    {
        for(j = 0; j < 128; ++j)
        {
            data1[i][j] = a;
            a += 0.1;
        }
    }

    float b = 0;
    for(i = 0; i < 3; ++i)
    {
        for(j = 0; j < 128; ++j)
        {
            data2[i][j] = b;
            b += 0.15;
        }
    }

    Mat m1 = Mat(2, 128, CV_32FC1, &data1);
    Mat m2 = Mat(3, 128, CV_32FC1, &data2);

    //cout << "Pierwsza macierz: " << endl;
    //cout << m1 << endl;
    //cout << "Druga macierz: " << endl;
    //cout << m2 << endl;

    vconcat(m1, allFeatures, allFeatures);
    vconcat(m2, allFeatures, allFeatures);

    cout << "Po konkatenacji: " << endl;
    cout << allFeatures << endl;

    chooseWords();

    cout << "\nWybrane słowa: " << endl;
    cout << selectedWords << endl;

   /* Mat difference(1, 128, CV_32FC1, Scalar(0));

    absdiff(m1.row(0), m2.row(0), difference);
    cout << difference << endl;

    float currentSum;
    for(int k = 0; k < 128; ++k)
        currentSum += difference.at<float>(0, k);

    float sum = 0;
    float current = 0;
    for(int i = 0; i < 128; ++i)
    {
        sum += current;
        current += 0.05;
    }

    cout << "Difference sum: " << currentSum << endl;
    cout << "Expected: " << sum << endl;
    */

    saveDictionary();
}

void VisualDictionary::testDictionaryK()
{
    this->constructDictionaryKMeans();

    this->saveDictionary();
}

void VisualDictionary::printMatrix(Mat matrix)
{
    std::cout << matrix << std::endl;
}

void VisualDictionary::prepareDictionary()
{
    std::ifstream f(this->dictionaryPath);
    //std::ifstream f("../dictionaryTest.xml");
    if(f.good())
    {
        std::cout << "Loading dictionary" << std::endl;
        this->loadDictionary();
    }
    else
    {
        std::cout << "Constructing and saving dictionary" << std::endl;
        this->constructDictionaryRandom();
        this->saveDictionary();
    }
}



