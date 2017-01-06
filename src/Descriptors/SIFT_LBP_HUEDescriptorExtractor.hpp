#ifndef BAGOFWORDS_SIFT_LBP_HUEDESCRIPTOREXTRACTOR_HPP
#define BAGOFWORDS_SIFT_LBP_HUEDESCRIPTOREXTRACTOR_HPP

#include "BasicDescriptor.hpp"
#include "SIFTandLBPSeparateDescriptorExtractor.hpp"
#include "HueDescriptor.hpp"

class SIFT_LBP_HUEDescriptorExtractor : public BasicDescriptor
{
private:
    const int HUE_HISTOGRAM_SIZE = 362;
    const int LBP_HISTOGRAM_SIZE = 256;
    SIFTandLBPSeparateDescriptorExtractor * SiftLbpExtractor;
public:
    SIFT_LBP_HUEDescriptorExtractor(int dictionarySize, const string &pathToDatabase, const string &pathToDictionary);
    virtual int getHistogramSize() override;
    virtual int getDictionarySize() override;
    virtual PictureInformation computeHistogram(string pathToPicture) override;
    ~SIFT_LBP_HUEDescriptorExtractor();
    virtual bool isReady() { return SiftLbpExtractor->isReady();}

};


#endif //BAGOFWORDS_SIFT_LBP_HUEDESCRIPTOREXTRACTOR_HPP
