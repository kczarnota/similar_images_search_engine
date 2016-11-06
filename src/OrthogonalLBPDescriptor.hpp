#ifndef BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP
#define BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP

#include "VisualDictionary.h"
#include <opencv2/imgproc.hpp>

class OrthogonalLBPDescriptor
{
public:
    static void computeOrthogonalLBPfeatures(const Mat & image, Mat & lbpFeatures, const vector<KeyPoint> & keyPoints);
};


#endif //BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP
