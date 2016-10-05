#ifndef BAGOFWORDS_SIFTDICTIONARY_H
#define BAGOFWORDS_SIFTDICTIONARY_H


#include "VisualDictionary.h"
using namespace std;

class SIFTDictionary : public VisualDictionary
{
public:
    SIFTDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath);
    void constructDictionaryRandom();
    void constructDictionaryKMeans();

};


#endif //BAGOFWORDS_SIFTDICTIONARY_H
