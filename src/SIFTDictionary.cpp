#include "SIFTDictionary.h"
#include <iostream>

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
                cout << "Could not open or find the image" << endl;
                exit(-1);
            }

            //std::cout << dir->path() << std::endl;
            SIFTDescriptorExtractor::computeSIFTfeatures(currentImage, currentFeatures, keyPoints);
            cout << "Rows: " << currentFeatures.rows << ", columns " << currentFeatures.cols << endl;
            vconcat(currentFeatures, allFeatures, allFeatures); //Dokonkatenuj pobrane cechy
        }
        ++dir;
    }

        chooseWords();
}

void SIFTDictionary::constructDictionaryKMeans()
{
    //Wybranie k losowych słów
    this->constructDictionaryRandom();
    cout << "Random selected" << endl;

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
        //Wyzerowanie macierzy
        for(int i = 0; i < this->selectedWords.rows; ++i)
        {
            classes[i] = Mat(0, vectorLength, CV_32FC1, Scalar(0));
        }

        shouldStop = true;

        //Przypisać do najbliższych klas
        for(int i = 0; i < this->allFeatures.rows; ++i) //każdą z cech trzeba przypisać do klasy
        {
            int minSumIndex = -1, minSum = std::numeric_limits<int>::max();
            this->allFeatures.row(i).copyTo(currentFeature.row(0)); //wybrana cecha
            for(int j = 0; j < this->selectedWords.rows; ++j) //przeglądam wszystkich reprezentantów klas
            {
                int currentSum = 0;
                this->selectedWords.row(j).copyTo(currentClass.row(0)); //wybrana klasa

                absdiff(currentClass, currentFeature, difference);
                // printMatrix(currentClass);
                // printMatrix(currentFeature);
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


/*        for (int l = 0; l < 5; ++l)
        {
            printMatrix(classes[l]);
            cout << "_________________________________________________________________________" << endl;
        }*/
        //Obliczyć średnie i sprawdzić czy nic się nie zmieniło
        for(int i = 0; i < this->selectedWords.rows; ++i) //dla każdej klasy
        {
            for(int j = 0; j < classes[i].rows; ++j) //przechodzę przez wszystkie wiersze i obliczam średnią
            {
                for(int k = 0; k < vectorLength; ++k)
                {
                    average.at<float>(0, k) += classes[i].row(j).at<float>(0, k); //suma wartości
                }
            }

            for(int k = 0; k < vectorLength; ++k)
            {
                average.at<float>(0, k) = (int)average.at<float>(0, k)/classes[i].rows; //wszystkie wartości podzielone przez liczbę cech
            }


            for(int k = 0; k < vectorLength; ++k)
            {
                if(average.at<float>(0, k) != this->selectedWords.row(i).at<float>(0, k))
                {
                    shouldStop = false;
                    average.row(0).copyTo(this->selectedWords.row(i)); //to zastępujemy stare nowym
                    break;
                }
            }

            for (int k = 0; k < vectorLength; ++k)
            {
                average.at<float>(0, k) = 0;
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
