#ifndef BAGOFWORDS_HOGLBPDESCRIPTOR_HPP
#define BAGOFWORDS_HOGLBPDESCRIPTOR_HPP


#include "BasicDescriptor.hpp"
#include "HOGDescriptorExtractor.hpp"
#include "LBPDescriptor.hpp"

class HOGLBPDescriptor : public BasicDescriptor
{
private:
    const int LBP_HISTOGRAM_SIZE = 256;
    HOGDescriptorExtractor * hogDescriptorExtractor;

public:
    virtual int getHistogramSize() override;
    virtual int getDictionarySize() override;
    virtual PictureInformation computeHistogram(string pathToPicture) override;
    HOGLBPDescriptor(int dictionarySize, string pathToDatabase, string pathToDictionary);
    ~HOGLBPDescriptor();
    virtual bool isReady() {return hogDescriptorExtractor->isReady();}
};


#endif //BAGOFWORDS_HOGLBPDESCRIPTOR_HPP
