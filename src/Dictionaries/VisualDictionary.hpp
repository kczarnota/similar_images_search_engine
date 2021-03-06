#ifndef BAGOFWORDS_VISUALDICTIONARY_H
#define BAGOFWORDS_VISUALDICTIONARY_H


#include <boost/filesystem.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace cv::xfeatures2d;
using namespace boost::filesystem;
using namespace std;

/*
 * Base class representing visual dictionary
 */
class VisualDictionary
{
protected:
    int sizeOfDictionary;
    string dictionaryPath;
    path startPath;
    Mat currentImage;
    Mat currentFeatures;
    Mat allFeatures;
    Mat selectedWords;
    int vectorLength;
    bool ready = false;

public:
    VisualDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath);

    virtual void constructDictionaryRandom()= 0;
    void prepareDictionary();
    void saveDictionary();
    void loadDictionary();
    Mat getWord(int rowNumber);
    int getSize();
    ~VisualDictionary() {};
    bool isReady() { return ready;}
    void setReady(bool b) {ready = b;}

protected:
    void chooseWords();
};

#endif //BAGOFWORDS_VISUALDICTIONARY_H
