#ifndef BAGOFWORDS_SIFTANDLBPDICTIONARY_H
#define BAGOFWORDS_SIFTANDLBPDICTIONARY_H


#include "VisualDictionary.h"

class SIFTandLBPDictionary : public VisualDictionary
{
public:
    SIFTandLBPDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath);
    void constructDictionaryRandom();
    void constructDictionaryKMeans();

};


#endif //BAGOFWORDS_SIFTANDLBPDICTIONARY_H
