#ifndef BAGOFWORDS_VISUALDICTIONARY_H
#define BAGOFWORDS_VISUALDICTIONARY_H


#include <boost/filesystem.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace cv::xfeatures2d;
using namespace boost::filesystem;
using namespace std;

/*
 * Klasa reprezentująca słownik
 */
class VisualDictionary
{
private:
    int sizeOfDictionary;
    //string dictionaryPath = "../dictionaryTest.xml";
    string dictionaryPath;
    path startPath;
    Mat currentImage;
    vector<KeyPoint> keyPoints;
    Mat currentFeatures;
    Mat allFeatures;
    Mat selectedWords;
    Ptr<SIFT> keyPointsDetector;
    Ptr<SIFT> featureExtractor;



public:
    VisualDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath);
    void constructDictionaryRandom();
    void constructDictionaryKMeans();
    void saveDictionary();
    void loadDictionary();
    Mat getWord(int rowNumber);
    int getSize();
    void testDictionary();
    void testDictionaryK();
    void printMatrix(Mat matrix);

private:
    void chooseWords();

    void prepareDictionary();
};

#endif //BAGOFWORDS_VISUALDICTIONARY_H
