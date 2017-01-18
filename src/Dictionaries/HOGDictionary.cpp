#include <iostream>
#include <QtWidgets/QProgressDialog>
#include <src/Model/BOW.hpp>
#include "HOGDictionary.hpp"

HOGDictionary::HOGDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath) : VisualDictionary(
        sizeOfDictionary, pathToDatabase, dictionaryPath)
{
    this->vectorLength = 36;
    this->startPath = path(pathToDatabase);
    this->sizeOfDictionary = sizeOfDictionary;
    this->currentFeatures = Mat(0, vectorLength, CV_32FC1, Scalar(0));
    this->allFeatures = Mat(0, vectorLength, CV_32FC1, Scalar(0));
    this->selectedWords = Mat(0, vectorLength, CV_32FC1, Scalar(0));
    this->dictionaryPath = dictionaryPath;
}

void HOGDictionary::constructDictionaryRandom()
{
    recursive_directory_iterator dir(this->startPath), end;
    int imgNumber = 0;
    int allFiles = BOW::countFiles(this->startPath.string());
    QProgressDialog progress("Preparing dictionary...", "Abort action", 0, allFiles);
    progress.setWindowModality(Qt::WindowModal);
    bool cancelled = false;
    while (dir != end)
    {
        file_status fs = status(dir->path());

        if (!is_directory(fs)) //Omit directories
        {
            //Load image
            currentImage = imread(dir->path().string(), CV_LOAD_IMAGE_ANYDEPTH);

            if (!currentImage.data)
            {
                cout << "Could not open or find the image" << endl;
                exit(-1);
            }

            currentFeatures = Mat(0, vectorLength, CV_32FC1, Scalar(0));
            HOGDescriptorExtractor::computeHOGfeatures(currentImage, currentFeatures);
            vconcat(currentFeatures, allFeatures, allFeatures);
            ++imgNumber;

            if (progress.wasCanceled())
            {
                cancelled = true;
                break;
            }

            progress.setValue(imgNumber);
        }
        ++dir;
    }

    if(!cancelled)
        setReady(true);

    chooseWords();
}

void HOGDictionary::constructDictionaryKMeans()
{

}
