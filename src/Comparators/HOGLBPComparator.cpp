#include "HOGLBPComparator.hpp"

double HOGLBPComparator::compare(const PictureInformation &p1, const PictureInformation &p2) const
{
    double sumOfMinElementsHOG = 0.0;
    double sumOfMinElementsLBP = 0.0;
    int size = p1.getHistogramSize();

    for(int i = 0; i < size; ++i)
    {
        if(i < HOGHistogramSize)
            sumOfMinElementsHOG += std::min(p1.getValueAt(i), p2.getValueAt(i));
        else
            sumOfMinElementsLBP += std::min(p1.getValueAt(i), p2.getValueAt(i));
    }

    double distanceSIFT = 1 - sumOfMinElementsHOG;
    double distanceLBP = 1 - sumOfMinElementsLBP;
    return distanceSIFT*weightHOG + distanceLBP*weightLBP;
}

HOGLBPComparator::HOGLBPComparator(int hogHistogramSize, double weightHog, double weightLBP)
{
    this->HOGHistogramSize = hogHistogramSize;
    this->weightHOG = weightHog;
    this->weightLBP = weightLBP;
}
