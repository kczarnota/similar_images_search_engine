#ifndef BAGOFWORDS_SIFTANDLBPDICTIONARY_H
#define BAGOFWORDS_SIFTANDLBPDICTIONARY_H


#include "VisualDictionary.hpp"
#include <opencv2/imgproc.hpp>

class SIFTandLBPDictionary : public VisualDictionary
{
private:
    vector<KeyPoint> keyPoints;

public:
    SIFTandLBPDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath);
    void constructDictionaryRandom();
    void constructDictionaryKMeans();
};


#endif //BAGOFWORDS_SIFTANDLBPDICTIONARY_H
