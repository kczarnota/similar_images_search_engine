#ifndef BAGOFWORDS_LBPDESCRIPTOR_H
#define BAGOFWORDS_LBPDESCRIPTOR_H
#include "VisualDictionary.h"
#include <opencv2/imgproc.hpp>

class LBPDescriptor
{
public:
    static void computeLBPfeatures(Mat image, Mat lbpFeatures, vector<KeyPoint> keyPoints);
};


#endif //BAGOFWORDS_LBPDESCRIPTOR_H
