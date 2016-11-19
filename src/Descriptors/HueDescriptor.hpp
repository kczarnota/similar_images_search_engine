#ifndef BAGOFWORDS_HUEDESCRIPTOR_HPP
#define BAGOFWORDS_HUEDESCRIPTOR_HPP


#include "BasicDescriptor.hpp"

class HueDescriptor : public BasicDescriptor
{
public:
    const static int HISTOGRAM_SIZE = 362;
    const static int PATCH_SIZE = 800;
    static void computeHueFeatures(const Mat & image, Mat & hueFeatures, const vector<KeyPoint> & keyPoints);
    virtual int getHistogramSize();
    virtual int getDictionarySize();
    virtual PictureInformation computeHistogram(string pathToPicture);
};


#endif //BAGOFWORDS_HUEDESCRIPTOR_HPP
