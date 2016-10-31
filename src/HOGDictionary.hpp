#ifndef BAGOFWORDS_HOGDICTIONARY_HPP
#define BAGOFWORDS_HOGDICTIONARY_HPP

#include "VisualDictionary.h"
#include "HOGDescriptorExtractor.hpp"
#include <opencv2/objdetect.hpp>

class HOGDictionary : public VisualDictionary
{
public:
    HOGDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath);
    void constructDictionaryRandom();
    void constructDictionaryKMeans();
};


#endif //BAGOFWORDS_HOGDICTIONARY_HPP
