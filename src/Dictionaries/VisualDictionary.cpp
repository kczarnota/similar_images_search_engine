#include "VisualDictionary.hpp"


void VisualDictionary::prepareDictionary()
{
    std::ifstream f(this->dictionaryPath);
    if(f.good())
    {
        cout << "Loading dictionary" << endl;
        this->loadDictionary();
        setReady(true);
    }
    else
    {
        cout << "Constructing and saving dictionary" << endl;
        this->constructDictionaryRandom();

        if(isReady())
            this->saveDictionary();
    }
}


/*
 * Chooses given number of features and makes them become words(they are kept in selectedWords)
 */
void VisualDictionary::chooseWords()
{
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
        numbers[x] = numbers[sizeOfNumbers - 1];
        sizeOfNumbers--;
        wordsLeftToChoose--;
    }


    for (int i = 0; i < sizeOfDictionary; ++i)
    {
        selectedWords.push_back(allFeatures.row(chosenNumbers[i]));
    }

    delete numbers;
    delete chosenNumbers;
}


/*
 * Saves dictionary to file
 */
void VisualDictionary::saveDictionary()
{
    FileStorage fs(this->dictionaryPath, FileStorage::WRITE);
    fs << "Dictionary" << this->selectedWords;
    fs.release();
}

/*
 * Loads dictionary from file
 */
void VisualDictionary::loadDictionary()
{
    FileStorage fs(this->dictionaryPath, FileStorage::READ);
    fs["Dictionary"] >> this->selectedWords;
    fs.release();
    this->sizeOfDictionary = this->selectedWords.rows;
}

Mat VisualDictionary::getWord(int rowNumber)
{
    return this->selectedWords.row(rowNumber);
}

int VisualDictionary::getSize()
{
    return this->selectedWords.rows;
}

VisualDictionary::VisualDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath)
{

}
