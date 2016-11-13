#ifndef BAGOFWORDS_COLORORTHOGONALLBPDESCRIPTOR_HPP
#define BAGOFWORDS_COLORORTHOGONALLBPDESCRIPTOR_HPP


#include "VisualDictionary.h"
#include "PictureInformation.h"

class ColorOrthogonalLBPDescriptor
{
private:
    static const int HISTOGRAM_SIZE = 96;
public:
    static PictureInformation computeHistrogramForWholePicture(string pathToPicture);
};


#endif //BAGOFWORDS_COLORORTHOGONALLBPDESCRIPTOR_HPP
