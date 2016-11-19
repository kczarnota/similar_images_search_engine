#include "SIFT_OrthogonalLBPComparator.hpp"

double SIFT_OrthogonalLBPComparator::compare(const PictureInformation &p1, const PictureInformation &p2) const
{
    double sumOfMinElementsSIFT = 0.0;
    double differenceBySum = 0.0;
    int size = p1.getHistogramSize();

    for(int i = 0; i < size; ++i)
    {
        double x = p1.getValueAt(i);
        double q = p2.getValueAt(i);
        if(i < SIFTHistogramSize)
            sumOfMinElementsSIFT += std::min(x, q);
        else
        {
            if(x + q != 0)
                differenceBySum += std::abs(x - q)/(x + q);
        }
    }

    double distanceSIFT = 1 - sumOfMinElementsSIFT;
    double distanceLBP = differenceBySum;
    return distanceSIFT*weightSIFT + distanceLBP*weightOrthogonalLBP;
}

SIFT_OrthogonalLBPComparator::SIFT_OrthogonalLBPComparator(int SIFTHistogramSize, double weightSIFT, double weightOrthogonalLBP)
{
    this->SIFTHistogramSize = SIFTHistogramSize;
    this->weightSIFT = weightSIFT;
    this->weightOrthogonalLBP = weightOrthogonalLBP;
}
