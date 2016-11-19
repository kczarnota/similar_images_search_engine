#ifndef BAGOFWORDS_SIFT_ORTHOGONALLBPDESCRIPTOREXTRACTOR_HPP
#define BAGOFWORDS_SIFT_ORTHOGONALLBPDESCRIPTOREXTRACTOR_HPP

#include "BasicDescriptor.hpp"
#include "SIFTDescriptorExtractor.hpp"
#include "OrthogonalLBPDescriptor.hpp"

class SIFT_OrthogonalLBPDescriptorExtractor : public BasicDescriptor
{
private:
    const int ORTHOGONAL_LBP_HISTOGRAM_SIZE = 32;
    SIFTDescriptorExtractor * siftDescriptorExtractor;

public:
    SIFT_OrthogonalLBPDescriptorExtractor(int dictionarySize, string pathToDatabase, string pathToDictionary);
    ~SIFT_OrthogonalLBPDescriptorExtractor();
    virtual int getHistogramSize() override;
    virtual int getDictionarySize() override;
    virtual PictureInformation computeHistogram(string pathToPicture) override;
};


#endif //BAGOFWORDS_SIFT_ORTHOGONALLBPDESCRIPTOREXTRACTOR_HPP
