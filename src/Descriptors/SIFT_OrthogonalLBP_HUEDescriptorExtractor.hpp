#ifndef BAGOFWORDS_SIFT_ORTHOGONALLBP_HUEDESCRIPTOREXTRACTOR_HPP
#define BAGOFWORDS_SIFT_ORTHOGONALLBP_HUEDESCRIPTOREXTRACTOR_HPP

#include "BasicDescriptor.hpp"
#include "SIFT_OrthogonalLBPDescriptorExtractor.hpp"
#include "HueDescriptor.hpp"

class SIFT_OrthogonalLBP_HUEDescriptorExtractor : public BasicDescriptor
{
    const int HUE_HISTOGRAM_SIZE = 362;
    const int ORTHOGONAL_LBP_HISTOGRAM_SIZE = 32;
    SIFT_OrthogonalLBPDescriptorExtractor * SiftOrthogonalLbpExtractor;
public:
    virtual int getHistogramSize() override;
    virtual int getDictionarySize() override;
    virtual PictureInformation computeHistogram(string pathToPicture) override;
    SIFT_OrthogonalLBP_HUEDescriptorExtractor(int dictionarySize, string pathToDatabase, string pathToDictionary);
    ~SIFT_OrthogonalLBP_HUEDescriptorExtractor();
    virtual bool isReady() { return SiftOrthogonalLbpExtractor->isReady();}

};


#endif //BAGOFWORDS_SIFT_ORTHOGONALLBP_HUEDESCRIPTOREXTRACTOR_HPP
