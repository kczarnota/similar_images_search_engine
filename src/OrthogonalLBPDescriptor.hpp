#ifndef BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP
#define BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP

#include "VisualDictionary.h"
#include "PictureInformation.h"
#include <opencv2/imgproc.hpp>

class OrthogonalLBPDescriptor
{
public:
    static void computeOrthogonalLBPfeatures(const Mat & image, Mat & lbpFeatures, const vector<KeyPoint> & keyPoints);
    static PictureInformation computeHistrogramForWholePicture(string pathToPicture);
};


#endif //BAGOFWORDS_ORTHOGONALLBPDESCRIPTOR_HPP
