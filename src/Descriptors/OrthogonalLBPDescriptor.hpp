#ifndef BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP
#define BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP

#include "BasicDescriptor.hpp"
#include <opencv2/imgproc.hpp>

class OrthogonalLBPDescriptor : public BasicDescriptor
{
private:
    static const int HISTOGRAM_SIZE = 32;
    static const int PATCH_SIZE = 128;
    static const int OFFSET = 16;
public:
    static void computeOrthogonalLBPfeatures(const Mat & image, Mat & lbpFeatures, const vector<KeyPoint> & keyPoints);
    static PictureInformation computeHistrogramForWholePicture(string pathToPicture);
    virtual int getHistogramSize();
    virtual int getDictionarySize();
    virtual PictureInformation computeHistogram(string pathToPicture);
    virtual bool isReady() { return true;}
};


#endif //BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP
