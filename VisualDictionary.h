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

class VisualDictionary
{
private:
    int sizeOfDictionary;
    //list<path> * imagesPath;
    path * startPath;
    Mat currentImage;
    vector<KeyPoint> * keyPoints;
    Mat * currentFeatures;
    Mat * allFeatures;
    Mat * selectedWords;
    Ptr<SIFT> keyPointsDetector;
    Ptr<SIFT> featureExtractor;



public:
    VisualDictionary(int sizeOfDictionary, string pathToDatabase);
    ~VisualDictionary();
    void initializeDictionary();

private:
    void listAllFiles(path * startPath);
    void chooseWords();
};

#endif //BAGOFWORDS_VISUALDICTIONARY_H
