#ifndef BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP
#define BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP

#include "BasicDescriptor.hpp"
#include <opencv2/imgproc.hpp>

class OrthogonalLBPDescriptor : public BasicDescriptor
{
private:
    static const int HISTOGRAM_SIZE = 32;
public:
    static void computeOrthogonalLBPfeatures(const Mat & image, Mat & lbpFeatures, const vector<KeyPoint> & keyPoints);
    static PictureInformation computeHistrogramForWholePicture(string pathToPicture);
    virtual int getHistogramSize();
    virtual int getDictionarySize();
    virtual PictureInformation computeHistogram(string pathToPicture);
};


#endif //BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP
