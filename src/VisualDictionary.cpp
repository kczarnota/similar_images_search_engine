#include "VisualDictionary.h"
#include <iostream>


VisualDictionary::VisualDictionary(int sizeOfDictionary, string pathToDatabase)
{
    this->startPath = path(pathToDatabase);
    this->sizeOfDictionary = sizeOfDictionary;
    this->allFeatures = Mat(0, 128, CV_32FC1, Scalar(0));
    this->selectedWords = Mat(0, 128, CV_32FC1, Scalar(0));
    this->keyPointsDetector = SIFT::create();
    this->featureExtractor = SIFT::create();
}


VisualDictionary::~VisualDictionary()
{
}


void VisualDictionary::constructDictionary()
{
    //listAllFiles(this->startPath);
    recursive_directory_iterator dir(this->startPath), end;

    //Go through all the images
    while (dir != end)
    {
        file_status fs = status(dir->path());

        if (!is_directory(fs))
        {
            //Load image
            currentImage = imread(dir->path().string(), CV_LOAD_IMAGE_ANYDEPTH);

            // Check for invalid input
            if (!currentImage.data)
            {
                cout << "Could not open or find the image" << std::endl;
                exit(-1);
            }

            std::cout << dir->path() << std::endl;
            keyPointsDetector->detect(currentImage, keyPoints);
            featureExtractor->compute(currentImage, keyPoints, currentFeatures);
            cout << "Rows: " << currentFeatures.rows << ", columns " << currentFeatures.cols << endl;
            //allFeatures->push_back(currentFeatures);
            vconcat(currentFeatures, allFeatures, allFeatures);
        }

        ++dir;
    }

    chooseWords();
}

void VisualDictionary::listAllFiles(path * startPath)
{
    recursive_directory_iterator dir(*startPath), end;

    while (dir != end)
    {
        file_status fs = status(dir->path());

        if (!is_directory(fs))
        {
            std::cout << dir->path() << std::endl;
        }

        ++dir;
    }
}

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


void VisualDictionary::saveDictionary()
{
    FileStorage fs(this->dictionaryPath, FileStorage::WRITE);
    fs << "Dictionary" << this->selectedWords;
    fs.release();
}

void VisualDictionary::loadDictionary()
{
    FileStorage fs(this->dictionaryPath, FileStorage::READ);
    fs["Dictionary"] >> this->selectedWords;
    fs.release();
    cout << "Rows: " << this->selectedWords.rows << " , columns: " << this->selectedWords.cols << endl;
}

Mat VisualDictionary::getRow(int rowNumber)
{
    return this->selectedWords.row(rowNumber);
}

int VisualDictionary::getSize()
{
    return this->sizeOfDictionary;
}



