#include "VisualDictionary.h"


void VisualDictionary::prepareDictionary()
{
    std::ifstream f(this->dictionaryPath);
    if(f.good())
    {
        cout << "Loading dictionary" << endl;
        this->loadDictionary();
    }
    else
    {
        cout << "Constructing and saving dictionary" << endl;
        this->constructDictionaryRandom();
        //this->constructDictionaryKMeans();
        this->saveDictionary();
    }
}


/*
 * Wybiera podaną liczbę cech jako słowa i dodaje je do slownika(przechowuje je w selectedWords)
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

VisualDictionary::VisualDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath)
{

}
