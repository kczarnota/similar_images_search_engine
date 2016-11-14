#ifndef BAGOFWORDS_SIFTLBPDESCRIPTOREXTRACTOR_HPP
#define BAGOFWORDS_SIFTLBPDESCRIPTOREXTRACTOR_HPP

#include "DescriptorUsingDictionary.hpp"
#include "SIFTandLBPDictionary.h"

class SIFTLBPDescriptorExtractor : public DescriptorUsingDictionary
{
private:
    static const int HISTOGRAM_SIZE = 192;
public:
    SIFTLBPDescriptorExtractor(int dictionarySize, string pathToDatabase, string pathToDictionary);
    ~SIFTLBPDescriptorExtractor();
    static void computeSIFTandLBPfeatures(const Mat & image, Mat & lbpFeatures);
    virtual int getHistogramSize();
    virtual int getDictionarySize();
    virtual PictureInformation computeHistogram(string pathToPicture);
};


#endif //BAGOFWORDS_SIFTLBPDESCRIPTOREXTRACTOR_HPP
