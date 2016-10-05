#ifndef BAGOFWORDS_SIFTANDLBPDICTIONARY_H
#define BAGOFWORDS_SIFTANDLBPDICTIONARY_H


#include "VisualDictionary.h"
#include <opencv2/imgproc.hpp>

class SIFTandLBPDictionary : public VisualDictionary
{
public:
    SIFTandLBPDictionary(int sizeOfDictionary, string pathToDatabase, string dictionaryPath);
    void constructDictionaryRandom();
    void constructDictionaryKMeans();

    void computeLBPfeatures(Mat image, Mat lbpFeatures);
};


#endif //BAGOFWORDS_SIFTANDLBPDICTIONARY_H
