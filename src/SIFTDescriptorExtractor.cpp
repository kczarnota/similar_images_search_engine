#include "SIFTDescriptorExtractor.hpp"

void SIFTDescriptorExtractor::computeSIFTfeatures(const Mat &currentImage, Mat &features, vector<KeyPoint> keyPoints)
{
    Ptr<SIFT> keyPointsDetector = SIFT::create();
    Ptr<SIFT> featureExtractor = SIFT::create();

    keyPointsDetector->detect(currentImage, keyPoints);
    featureExtractor->compute(currentImage, keyPoints, features);
}
