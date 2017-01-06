#include "SIFT_LBP_HUEComparator.hpp"

double SIFT_LBP_HUEComparator::compare(const PictureInformation &p1, const PictureInformation &p2) const
{
    double sumOfMinElementsSIFT = 0.0;
    double sumOfMinElementsLBP = 0.0;
    double sumOfMinElementsHUE = 0.0;
    int size = p1.getHistogramSize();

    for(int i = 0; i < size; ++i)
    {
        if(i < SIFTHistogramSize)
            sumOfMinElementsSIFT += std::min(p1.getValueAt(i), p2.getValueAt(i));
        else if(i < SIFTHistogramSize + LBP_HISTOGRAM_SIZE)
            sumOfMinElementsLBP += std::min(p1.getValueAt(i), p2.getValueAt(i));
        else
            sumOfMinElementsHUE += std::min(p1.getValueAt(i), p2.getValueAt(i));
    }

    double distanceSIFT = 1 - sumOfMinElementsSIFT;
    double distanceLBP = 1 - sumOfMinElementsLBP;
    double distanceHUE = 1 - sumOfMinElementsHUE;
    return distanceSIFT*getSIFTWeight() + distanceLBP*getLBPWeight() + distanceHUE*getHUEWeight();
}

SIFT_LBP_HUEComparator::SIFT_LBP_HUEComparator(int SIFTDictionarySize)
{
    this->SIFTHistogramSize = SIFTDictionarySize;
}
