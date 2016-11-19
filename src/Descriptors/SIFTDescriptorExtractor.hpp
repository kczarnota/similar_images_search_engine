#ifndef BAGOFWORDS_SIFTDESCRIPTOREXTRACTOR_HPP
#define BAGOFWORDS_SIFTDESCRIPTOREXTRACTOR_HPP

#include "DescriptorUsingDictionary.hpp"
#include "../Dictionaries/SIFTDictionary.hpp"

class SIFTDescriptorExtractor : public DescriptorUsingDictionary
{
private:
    static const int HISTOGRAM_SIZE = 128;
public:
    SIFTDescriptorExtractor(int dictionarySize, string pathToDatabase, string pathToDictionary);
    ~SIFTDescriptorExtractor();
    virtual int getHistogramSize();
    virtual int getDictionarySize();
    virtual PictureInformation computeHistogram(string pathToPicture);
    static void computeSIFTfeatures(const Mat & currentImage, Mat & features, vector<KeyPoint> & keyPoints);
};


#endif //BAGOFWORDS_SIFTDESCRIPTOREXTRACTOR_HPP
