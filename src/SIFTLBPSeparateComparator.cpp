#include "SIFTLBPSeparateComparator.hpp"

double SIFTLBPSeparateComparator::compare(const PictureInformation &p1, const PictureInformation &p2) const
{
    double sumOfMinElementsSIFT = 0.0;
    double sumOfMinElementsLBP = 0.0;
    int size = p1.getHistogramSize();

    for(int i = 0; i < size; ++i)
    {
        if(i < SIFTHistogramSize)
            sumOfMinElementsSIFT += std::min(p1.getValueAt(i), p2.getValueAt(i));
        else
            sumOfMinElementsLBP += std::min(p1.getValueAt(i), p2.getValueAt(i));
    }

    double distanceSIFT = 1 - sumOfMinElementsSIFT;
    double distanceLBP = 1 - sumOfMinElementsLBP;
    return distanceSIFT*weightSIFT + distanceLBP*weightLBP;
}

SIFTLBPSeparateComparator::SIFTLBPSeparateComparator(int SIFTDictionarySize, int weightSIFT,int weightLBP)
{
    this->SIFTHistogramSize = SIFTDictionarySize;
    this->weightSIFT = weightSIFT;
    this->weightLBP = weightLBP;
}
