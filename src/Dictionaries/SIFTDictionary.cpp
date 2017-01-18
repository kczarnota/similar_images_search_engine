#include "SIFTDictionary.hpp"
#include <iostream>
#include <QtWidgets/QProgressDialog>
#include <src/Model/BOW.hpp>


SIFTDictionary::SIFTDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath) : VisualDictionary(
        sizeOfDictionary, pathToDatabase, dictionaryPath)
{
    vectorLength = 128;
    this->startPath = path(pathToDatabase);
    this->sizeOfDictionary = sizeOfDictionary;
    this->currentFeatures = Mat(0, 128, CV_32FC1, Scalar(0));
    this->allFeatures = Mat(0, vectorLength, CV_32FC1, Scalar(0));
    this->selectedWords = Mat(0, vectorLength, CV_32FC1, Scalar(0));
    this->dictionaryPath = dictionaryPath;
}

void SIFTDictionary::constructDictionaryRandom()
{
    recursive_directory_iterator dir(this->startPath), end;

    int allFiles = BOW::countFiles(this->startPath.string());
    QProgressDialog progress("Preparing dictionary...", "Abort action", 0, allFiles);
    progress.setWindowModality(Qt::WindowModal);
    int imgNum = 0;
    bool cancelled = false;
    while (dir != end)
    {
        file_status fs = status(dir->path());

        if (!is_directory(fs))
        {
            currentImage = imread(dir->path().string(), CV_LOAD_IMAGE_ANYDEPTH);

            if (!currentImage.data)
            {
                cout << "Could not open or find the image" << endl;
                exit(-1);
            }

            SIFTDescriptorExtractor::computeSIFTfeatures(currentImage, currentFeatures, keyPoints);
            vconcat(currentFeatures, allFeatures, allFeatures);
            if (progress.wasCanceled())
            {
                cancelled = true;
                break;
            }

            progress.setValue(++imgNum);
        }
        ++dir;
    }

    if(!cancelled)
    {
        setReady(true);
        chooseWords();
    }
}

void SIFTDictionary::constructDictionaryKMeans()
{
    this->constructDictionaryRandom();

    bool shouldStop = false;
    Mat *classes = new Mat[this->selectedWords.rows];
    Mat currentClass(1, vectorLength, CV_32FC1, Scalar(0));
    Mat currentFeature(1, vectorLength, CV_32FC1, Scalar(0));
    Mat difference(1, vectorLength, CV_32FC1, Scalar(0));
    Mat average(1, vectorLength, CV_32FC1, Scalar(0));

    int iterations = 0;
    while(!shouldStop && iterations < 10)
    {
        cout << iterations++ << endl;

        for(int i = 0; i < this->selectedWords.rows; ++i)
        {
            classes[i] = Mat(0, vectorLength, CV_32FC1, Scalar(0));
        }

        shouldStop = true;

        for(int i = 0; i < this->allFeatures.rows; ++i)
        {
            int minSumIndex = -1, minSum = std::numeric_limits<int>::max();
            this->allFeatures.row(i).copyTo(currentFeature.row(0));
            for(int j = 0; j < this->selectedWords.rows; ++j)
            {
                int currentSum = 0;
                this->selectedWords.row(j).copyTo(currentClass.row(0));

                absdiff(currentClass, currentFeature, difference);

                for(int k = 0; k < vectorLength; ++k)
                {
                    currentSum += difference.at<float>(0, k);
                }

                if(currentSum < minSum)
                {
                    minSum = currentSum;
                    minSumIndex = j;
                }
            }
            classes[minSumIndex].push_back(currentFeature.row(0));
        }

        for(int i = 0; i < this->selectedWords.rows; ++i)
        {
            for(int j = 0; j < classes[i].rows; ++j)
            {
                for(int k = 0; k < vectorLength; ++k)
                {
                    average.at<float>(0, k) += classes[i].row(j).at<float>(0, k);
                }
            }

            for(int k = 0; k < vectorLength; ++k)
            {
                average.at<float>(0, k) = (int)average.at<float>(0, k)/classes[i].rows;
            }


            for(int k = 0; k < vectorLength; ++k)
            {
                if(average.at<float>(0, k) != this->selectedWords.row(i).at<float>(0, k))
                {
                    shouldStop = false;
                    average.row(0).copyTo(this->selectedWords.row(i));
                    break;
                }
            }

            for (int k = 0; k < vectorLength; ++k)
            {
                average.at<float>(0, k) = 0;
            }
        }
    }

    delete []classes;
}
