#ifndef BAGOFWORDS_SIFTDICTIONARY_H
#define BAGOFWORDS_SIFTDICTIONARY_H


#include "VisualDictionary.h"
using namespace std;

class SIFTDictionary : public VisualDictionary
{
private:
    Ptr<SIFT> keyPointsDetector;
    Ptr<SIFT> featureExtractor;
    vector<KeyPoint> keyPoints;
public:
    SIFTDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath);
    void constructDictionaryRandom();
    void constructDictionaryKMeans();

};


#endif //BAGOFWORDS_SIFTDICTIONARY_H
