#ifndef BAGOFWORDS_SIFTDESCRIPTOREXTRACTOR_HPP
#define BAGOFWORDS_SIFTDESCRIPTOREXTRACTOR_HPP

#include "VisualDictionary.h"


class SIFTDescriptorExtractor
{
public:
    static void computeSIFTfeatures(const Mat & currentImage, Mat & features, vector<KeyPoint> keyPoints);
};


#endif //BAGOFWORDS_SIFTDESCRIPTOREXTRACTOR_HPP
