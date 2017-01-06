#ifndef BAGOFWORDS_LBPDESCRIPTOR_H
#define BAGOFWORDS_LBPDESCRIPTOR_H
#include "../Dictionaries/VisualDictionary.hpp"
#include "../Model/PictureInformation.hpp"
#include "BasicDescriptor.hpp"
#include <opencv2/imgproc.hpp>

class LBPDescriptor : public BasicDescriptor
{
public:
    const static int HISTOGRAM_SIZE = 256;
    const static int PATCH_SIZE = 64;
    static void computeLBPfeatures(const Mat & image, Mat & lbpFeatures, const vector<KeyPoint> & keyPoints);
    static PictureInformation computeHistrogramForWholePicture(string Path);
    virtual int getHistogramSize();
    virtual int getDictionarySize();
    virtual PictureInformation computeHistogram(string pathToPicture);
    virtual bool isReady() { return true;}
};


#endif //BAGOFWORDS_LBPDESCRIPTOR_H
