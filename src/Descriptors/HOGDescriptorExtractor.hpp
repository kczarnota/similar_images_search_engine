#ifndef BAGOFWORDS_HOGDESCRIPTOR_HPP
#define BAGOFWORDS_HOGDESCRIPTOR_HPP

#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include "DescriptorUsingDictionary.hpp"
#include "../Dictionaries/HOGDictionary.hpp"

using namespace cv;

class HOGDescriptorExtractor : public DescriptorUsingDictionary
{
private:
    static const int HISTOGRAM_SIZE = 36;
public:
    HOGDescriptorExtractor(int dictionarySize, string pathToDatabase, string pathToDictionary);
    ~HOGDescriptorExtractor();
    static void computeHOGfeatures(const Mat & image, Mat & lbpFeatures);
    virtual int getHistogramSize();
    virtual int getDictionarySize();
    virtual PictureInformation computeHistogram(string pathToPicture);
};


#endif //BAGOFWORDS_HOGDESCRIPTOR_HPP
