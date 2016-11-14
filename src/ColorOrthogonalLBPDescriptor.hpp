#ifndef BAGOFWORDS_COLORORTHOGONALLBPDESCRIPTOR_HPP
#define BAGOFWORDS_COLORORTHOGONALLBPDESCRIPTOR_HPP


#include "BasicDescriptor.hpp"

class ColorOrthogonalLBPDescriptor : public BasicDescriptor
{
private:
    static const int HISTOGRAM_SIZE = 96;
public:
    static PictureInformation computeHistrogramForWholePicture(string pathToPicture);
    virtual int getHistogramSize();
    virtual int getDictionarySize();
    virtual PictureInformation computeHistogram(string pathToPicture);
};


#endif //BAGOFWORDS_COLORORTHOGONALLBPDESCRIPTOR_HPP
