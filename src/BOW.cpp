#include "BOW.h"

BOW::BOW(int sizeOfDictionary, string pathToDatabase)
{
    this->visualDictionary = new VisualDictionary(sizeOfDictionary, pathToDatabase);
    this->pictureDatabase = new PictureDatabase(sizeOfDictionary);
}

BOW::~BOW()
{
    delete this->visualDictionary;
    delete this->pictureDatabase;
}

void BOW::prepareDictionary()
{
    std::ifstream f("../dictionary.xml");
    if(f.good())
    {
        std::cout << "Loading" << std::endl;
        this->visualDictionary->loadDictionary();
    }
    else
    {
        std::cout << "Constructing and saving" << std::endl;
        this->visualDictionary->constructDictionary();
        this->visualDictionary->saveDictionary();
    }
}

void BOW::addPictureToDatabase(string pathToPicture)
{
    PictureInformation pi = this->computeHistogram(pathToPicture);
    this->pictureDatabase->addPicture(pi);

   /* for(int n = 0; n < this->visualDictionary->getSize(); ++n)
    {
        std::cout << pictureInformation.getValueAt(n) << std::endl;
    } */

   /* features.row(0).copyTo(currentRow.row(0));
    this->visualDictionary->getRow(0).copyTo(currentWord.row(0));

    absdiff(currentRow, currentWord, difference);

    Scalar totalDifference = sum(difference);
    int intSum = 0;

    for(int i = 0; i < 128; ++i)
        intSum += difference.at<float>(0, i);  //If matrix is of type CV_32F then use Mat.at<float>(y,x).


    std::cout << totalDifference[0] << endl;
    std::cout << intSum << std::endl; */


  /*  std::cout << currentRow.rows << " " << currentRow.cols << std::endl;
    std::cout << currentWord.rows << " " << currentWord.cols << std::endl;
    std::cout << difference.rows << " " << difference.cols << std::endl;

    std::cout << currentRow.col(3) << std::endl;
    std::cout << currentWord.col(3) << std::endl;
    std::cout << difference.col(3) << std::endl;
    std::cout << std::endl;

    std::cout << currentRow.col(4) << std::endl;
    std::cout << currentWord.col(4) << std::endl;
    std::cout << difference.col(4) << std::endl;
    std::cout << std::endl;

    std::cout << currentRow.col(5) << std::endl;
    std::cout << currentWord.col(5) << std::endl;
    std::cout << difference.col(5) << std::endl;
    std::cout << std::endl; */
}

void BOW::createDatabase(string pathToDatabase)
{
    this->updateDatabase(pathToDatabase);
    this->saveDatabase();
}

void BOW::saveDatabase()
{
    std::ofstream ofs("/home/konrad/Dokumenty/CLionProjects/BagOfWords/BazaDanych/database");
    boost::archive::text_oarchive oa(ofs);
    oa << this->pictureDatabase;
}

void BOW::loadDatabase()
{
    // create and open an archive for input
    std::ifstream ifs("/home/konrad/Dokumenty/CLionProjects/BagOfWords/BazaDanych/database");
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> this->pictureDatabase;
}

void BOW::listDatabase()
{
    for(int i = 0; i < this->pictureDatabase->getSize(); ++i)
    {
        PictureInformation pi = this->pictureDatabase->getPicture(i);
        cout << pi.getName() << endl;
        for(int j = 0; j < this->visualDictionary->getSize(); ++j)
        {
            cout << pi.getValueAt(j) << endl;
        }
    }
}


void BOW::updateDatabase(string pathToDatabase)
{
    path p(pathToDatabase);
    recursive_directory_iterator dir(p), end;

    while (dir != end)
    {
        file_status fs = status(dir->path());

        if (!is_directory(fs))
        {
            this->addPictureToDatabase(dir->path().string());
        }

        ++dir;
    }
}

string BOW::makeQuery(string pathToPicture)
{
    PictureInformation queryPicture = this->computeHistogram(pathToPicture);

    int minIndex = 0;
    double minDistance = this->comparePictureHistograms(queryPicture, this->pictureDatabase->getPicture(0));
    double distance = minDistance;

    for(int i = 1; i < this->visualDictionary->getSize(); ++i)
    {
        distance = this->comparePictureHistograms(queryPicture, this->pictureDatabase->getPicture(i));

        if(distance < minDistance)
        {
            minDistance = distance;
            minIndex = i;
        }
    }

    PictureInformation mostSimilarPicture = this->pictureDatabase->getPicture(minIndex);
    return mostSimilarPicture.getName();
}

double BOW::comparePictureHistograms(PictureInformation p1, PictureInformation p2)
{
    double distance = 0.0, sumOfMinElements = 0.0;

    for(int i = 0; i < 128; ++i)
        sumOfMinElements += std::min(p1.getValueAt(i), p2.getValueAt(i));

    distance = 1 - sumOfMinElements;
    return distance;
}


PictureInformation BOW::computeHistogram(string pathToPicture)
{
    Ptr<SIFT> keyPointsDetector = SIFT::create();
    Ptr<SIFT> featureExtractor= SIFT::create();
    vector<KeyPoint> keyPoints;
    Mat features = Mat(0, 128, CV_32FC1, Scalar(0));

    cv::Mat picture = imread(pathToPicture, CV_LOAD_IMAGE_ANYDEPTH);

    if (!picture.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    PictureInformation pictureInformation(pathToPicture, this->visualDictionary->getSize());

    keyPointsDetector->detect(picture, keyPoints);
    featureExtractor->compute(picture, keyPoints, features);

    Mat currentRow(1, 128, CV_32FC1, Scalar(0));
    Mat currentWord(1, 128, CV_32FC1, Scalar(0));
    Mat difference(1, 128, CV_32FC1, Scalar(0));

    std::cout << features.rows << std::endl;

    int i, j;
    for(i = 0; i < features.rows; ++i)
    {
        int minSumIndex = 0, minSum = -1;
        features.row(i).copyTo(currentRow.row(0));
        for(j = 0; j < this->visualDictionary->getSize(); ++j)
        {
            int currentSum = 0;
            this->visualDictionary->getWord(j).copyTo(currentWord.row(0));
            absdiff(currentRow, currentWord, difference);

            for(int k = 0; k < 128; ++k)
                currentSum += difference.at<float>(0, k);

            if(minSum == -1 || currentSum < minSum)
            {
                minSum = currentSum;
                minSumIndex = j;
            }
        }
        pictureInformation.addOneAt(minSumIndex);
    }

    pictureInformation.normalize(features.rows);

    return pictureInformation;
}
















