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

/* Sprawdza czy istnieje już słownik - jeśli tak to go wczytuje, w przeciwnym wypadku tworzy go */
void BOW::prepareDictionary()
{
    std::ifstream f("../dictionary.xml");
    //std::ifstream f("../dictionaryTest.xml");
    if(f.good())
    {
        std::cout << "Loading dictionary" << std::endl;
        this->visualDictionary->loadDictionary();
    }
    else
    {
        std::cout << "Constructing and saving dictionary" << std::endl;
        this->visualDictionary->constructDictionaryRandom();
        this->visualDictionary->saveDictionary();
    }
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
    cout << "Database loaded" << endl;
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

    /*for(int i = 0; i < this->pictureDatabase->getSize(); ++i)
    {
        double sum = 0.0;
        PictureInformation pi = this->pictureDatabase->getPicture(i);
        for(int j = 0; j < this->visualDictionary->getSize(); ++j)
        {
            sum += pi.getValueAt(j);
        }
        cout <<"Obrazek numer " << i << "" << sum << endl;
    } */
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

void BOW::addPictureToDatabase(string pathToPicture)
{
    PictureInformation pi = this->computeHistogram(pathToPicture);
    this->pictureDatabase->addPicture(pi);
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

    keyPointsDetector->detect(picture, keyPoints);
    featureExtractor->compute(picture, keyPoints, features);

    PictureInformation pictureInformation(pathToPicture, this->visualDictionary->getSize());


    Mat currentRow(1, 128, CV_32FC1, Scalar(0));
    Mat currentWord(1, 128, CV_32FC1, Scalar(0));
    Mat difference(1, 128, CV_32FC1, Scalar(0));

    std::cout << features.rows << std::endl;
    //std::cout << pathToPicture << std::endl;

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

   /* double total = 0;
    for(int a = 0; a < this->visualDictionary->getSize(); ++a)
    {
        total += pictureInformation.getValueAt(a);
    }
    cout << "Total value: " << total << endl;

    for(int i = 0; i < this->visualDictionary->getSize(); ++i)
        cout << pictureInformation.getValueAt(i) << endl; */

    return pictureInformation;
}


ResultVector BOW::makeQuery(string pathToPicture, int resultNumber)
{
    PictureInformation queryPicture = this->computeHistogram(pathToPicture);

    int minIndex = 0;
    double distances[this->pictureDatabase->getSize()];
    double minDistance = this->comparePictureHistograms(queryPicture, this->pictureDatabase->getPicture(0));
    double distance = minDistance;
    distances[0] = distance;
    ResultVector resultVector(resultNumber, 2.0);

    for(int i = 1; i < this->pictureDatabase->getSize(); ++i)//this->visualDictionary->getSize(); ++i)
    {
        distance = this->comparePictureHistograms(queryPicture, this->pictureDatabase->getPicture(i));
        distances[i] = distance;
        resultVector.tryAdd(make_pair(this->pictureDatabase->getPicture(i).getName(), distance));
    }

  /*  cout << "Porównano z :" << k << endl;
    for(int i = 0; i < 200; ++i)
    {
        double sum = 0;
        for(int j = 0; j < 10000; ++j)
        {
            sum += this->pictureDatabase->getPicture(i).getValueAt(j);
        }
        cout << sum << endl;
    } */


    this->computePrecisionAndRecall(resultVector, resultNumber);

   /* for(int i = 0; i < this->pictureDatabase->getSize(); ++i)
    {
        cout << distances[i] << endl;
    } */

    return resultVector;
}

double BOW::comparePictureHistograms(PictureInformation p1, PictureInformation p2)
{
    double distance = 0.0, sumOfMinElements = 0.0;

    for(int i = 0; i < this->visualDictionary->getSize(); ++i)
        sumOfMinElements += std::min(p1.getValueAt(i), p2.getValueAt(i));

    distance = 1 - sumOfMinElements;
    return distance;
}

void BOW::computePrecisionAndRecall(ResultVector vec, int numberOfAskedPictures)
{
    vector<string> splittedString = this->splitString(vec.getPairAt(0).first);
    string queryPictureCategory = splittedString[3];
    double numberOfSimilarPictures = 0.0;
    string currentPicCategory;

    for(int i = 1; i < vec.getSize(); ++i)
    {
        splittedString = this->splitString(vec.getPairAt(i).first);
        currentPicCategory = splittedString[3];

        if(queryPictureCategory == currentPicCategory)
            ++numberOfSimilarPictures;
    }

    this->precision = numberOfSimilarPictures/(numberOfAskedPictures - 1);
    this->recall = numberOfSimilarPictures/100;
}



std::pair<double, double> BOW::getPrecisionAndRecall(ResultVector vec, int numberOfAskedPictures)
{
    vector<string> splittedString = this->splitString(vec.getPairAt(0).first);
    string queryPictureCategory = splittedString[3];
    double numberOfSimilarPictures = 0.0;
    string currentPicCategory;

    for(int i = 1; i < numberOfAskedPictures; ++i)
    {
        splittedString = this->splitString(vec.getPairAt(i).first);
        currentPicCategory = splittedString[3];

        if(queryPictureCategory == currentPicCategory)
            ++numberOfSimilarPictures;
    }

    return std::make_pair(numberOfSimilarPictures/(numberOfAskedPictures - 1), numberOfSimilarPictures/100);
}



vector<string> BOW::splitString(string stringToSplit)
{
    stringstream stream(stringToSplit);
    std::string stringPart = "/";
    std::vector<std::string> splittedString;

    while(std::getline(stream, stringPart, '/'))
    {
        splittedString.push_back(stringPart);
    }
    return splittedString;
}

void BOW::testPicture(int min, int max, int step, int questionNumber)
{
    for(int i = 0; i < questionNumber; ++i)
    {
        string pathToPic;
        cout << "Podaj nazwe pliku" << endl;
        cin >> pathToPic;
        for (int current = min; current <= max; current += step)
        {
            ResultVector res = this->makeQuery(pathToPic,
                                               current);//("/home/konrad/Dokumenty/CLionProjects/BagOfWords/BazaDanych/autobus2.jpg");
            cout << "Query for: " << current << endl;
            cout << "Precision: " << this->getPrecision() << ", recall: " << this->getRecall() << endl;
        }
    }
}

void BOW::testDictionary()
{
    Mat difference(1, 128, CV_32FC1, Scalar(0));

    for(int i = 0; i < this->visualDictionary->getSize(); ++i)
    {
        for(int j = i + 1; j < this->visualDictionary->getSize(); ++j)
        {
            absdiff(this->visualDictionary->getWord(i), this->visualDictionary->getWord(j), difference);

            double sum = 0;
            int k;
            for(k = 0; k < 128; ++k)
            {
                sum += difference.at<float>(0, k);;
            }

            if(sum == 0)
                cout << sum << endl;
        }
    }
}



