#include "SIFTandLBPDictionary.h"
#include <iostream>

SIFTandLBPDictionary::SIFTandLBPDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath) : VisualDictionary(
        sizeOfDictionary, pathToDatabase, dictionaryPath)
{
    vectorLength = 192;
    this->startPath = path(pathToDatabase);
    this->sizeOfDictionary = sizeOfDictionary;
    this->currentFeatures = Mat(0, 128, CV_32FC1, Scalar(0));
    this->allFeatures = Mat(0, vectorLength, CV_32FC1, Scalar(0));
    this->selectedWords = Mat(0, vectorLength, CV_32FC1, Scalar(0));
    this->keyPointsDetector = SIFT::create();
    this->featureExtractor = SIFT::create();
    this->dictionaryPath = dictionaryPath;
}

void SIFTandLBPDictionary::constructDictionaryRandom()
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
            keyPointsDetector->detect(currentImage, keyPoints);
            featureExtractor->compute(currentImage, keyPoints, currentFeatures);
            Mat featuresSIFTandLBP = Mat(currentFeatures.rows, 192, CV_32FC1, Scalar(0));
            Mat featuresLBP = Mat(currentFeatures.rows, 64, CV_32FC1, Scalar(0));
            computeLBPfeatures(currentImage, featuresLBP);

            for (int i = 0; i < currentFeatures.rows; ++i)
            {
                for (int j = 0; j < 192; ++j)
                {
                    if(j < 128)
                    {
                        featuresSIFTandLBP.at<float>(i, j) = currentFeatures.at<float>(i, j);
                    }
                    else
                    {
                        featuresSIFTandLBP.at<float>(i, j) = featuresLBP.at<float>(i, j % 64);
                    }
                }
            }

            cout << "Rows: " << featuresSIFTandLBP.rows << ", columns " << featuresSIFTandLBP.cols << endl;
            vconcat(featuresSIFTandLBP, allFeatures, allFeatures); //Dokonkatenuj pobrane cechy
        }
        ++dir;
    }

    chooseWords();
}






void SIFTandLBPDictionary::constructDictionaryKMeans()
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

void SIFTandLBPDictionary::computeLBPfeatures(Mat image, Mat lbpFeatures)
{
    int counter = 0;
    for(KeyPoint p : keyPoints)
    {
        Mat dest;
        getRectSubPix(image, Size(10, 10), Point2f(p.pt.x, p.pt.y), dest);

        int flatNumber = 0;
        for(int r = 1; r < 9; ++r)
        {
            for (int c = 1; c < 9; ++c)
            {
                Scalar intensity = dest.at<uchar>(r, c);
                uchar mid = intensity.val[0];

                unsigned char number = 0;

                //left middle
                intensity = dest.at<uchar>(r, c - 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 7;
                }

                //left bottom
                intensity = dest.at<uchar>(r + 1, c - 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 6;
                }

                //bottom middle
                intensity = dest.at<uchar>(r + 1, c);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 5;
                }

                //rigth bottom
                intensity = dest.at<uchar>(r + 1, c + 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 4;
                }

                //right middle
                intensity = dest.at<uchar>(r, c + 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 3;
                }

                //right top
                intensity = dest.at<uchar>(r - 1, c + 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 2;
                }

                //right middle
                intensity = dest.at<uchar>(r - 1, c);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 1;
                }

                //left top
                intensity = dest.at<uchar>(r - 1, c - 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1;
                }

                lbpFeatures.at<float>(counter, flatNumber) = number;
                flatNumber++;
            }
        }
        counter++;
    }
}
