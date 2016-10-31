#ifndef BAGOFWORDS_SIFTDICTIONARY_H
#define BAGOFWORDS_SIFTDICTIONARY_H


#include "VisualDictionary.h"
#include "SIFTDescriptorExtractor.hpp"

using namespace std;

class SIFTDictionary : public VisualDictionary
{
private:
    vector<KeyPoint> keyPoints;
public:
    SIFTDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath);
    void constructDictionaryRandom();
    void constructDictionaryKMeans();

};


#endif //BAGOFWORDS_SIFTDICTIONARY_H
