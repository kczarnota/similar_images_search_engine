#ifndef BAGOFWORDS_HOGDESCRIPTOR_HPP
#define BAGOFWORDS_HOGDESCRIPTOR_HPP

#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include "VisualDictionary.h"

class HOGDescriptorExtractor
{
public:
    static void computeHOGfeatures(const Mat & image, Mat & lbpFeatures);
};


#endif //BAGOFWORDS_HOGDESCRIPTOR_HPP
