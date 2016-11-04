#ifndef BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP
#define BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP

#include "VisualDictionary.h"
#include <opencv2/imgproc.hpp>

class OrthogonalLBPDescriptor
{
public:
    static void computeOrthogonalLBPfeatures(Mat image, Mat lbpFeatures, vector<KeyPoint> keyPoints);
};


#endif //BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP
