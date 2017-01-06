#ifndef BAGOFWORDS_DESCRIPTORUSINGDICTIONARY_HPP
#define BAGOFWORDS_DESCRIPTORUSINGDICTIONARY_HPP

#include "BasicDescriptor.hpp"
#include "../Dictionaries/VisualDictionary.hpp"

class DescriptorUsingDictionary : public BasicDescriptor
{
protected:
    VisualDictionary * visualDictionary;
    PictureInformation getHistogramBasedOnDictionary(string pathToPicture, Mat &features);

public:
    virtual int getHistogramSize() = 0;
    virtual int getDictionarySize() = 0;
    virtual PictureInformation computeHistogram(string pathToPicture) = 0;
    virtual ~DescriptorUsingDictionary() {};
    virtual bool isReady() {return visualDictionary->isReady();};
};


#endif //BAGOFWORDS_DESCRIPTORUSINGDICTIONARY_HPP
