#include "SIFT_OrthogonalLBP_HUEComparator.hpp"

double SIFT_OrthogonalLBP_HUEComparator::compare(const PictureInformation &p1, const PictureInformation &p2) const
{
    double sumOfMinElementsSIFT = 0.0;
    double differenceBySum = 0.0;
    double sumOfMinElementsHUE = 0.0;
    int size = p1.getHistogramSize();

    for(int i = 0; i < size; ++i)
    {
        double x = p1.getValueAt(i);
        double q = p2.getValueAt(i);
        if(i < SIFTHistogramSize)
            sumOfMinElementsSIFT += std::min(x, q);
        else if(i < SIFTHistogramSize + ORTHOGONAL_LBP_HISTOGRAM_SIZE)
        {
            if(x + q != 0)
                differenceBySum += std::abs(x - q)/(x + q);
        }
        else
            sumOfMinElementsHUE += std::min(x, q);
    }

    double distanceSIFT = 1 - sumOfMinElementsSIFT;
    double distanceHUE = 1 - sumOfMinElementsHUE;
    return distanceSIFT*weightSIFT + differenceBySum*weightOrthogonalLBP + distanceHUE*weightHUE;
}

SIFT_OrthogonalLBP_HUEComparator::SIFT_OrthogonalLBP_HUEComparator(int SIFTHistogramSize, double weightSIFT, double weightOrthogonalLBP, double weightHUE)
{
    this->SIFTHistogramSize = SIFTHistogramSize;
    this->weightSIFT = weightSIFT;
    this->weightOrthogonalLBP  = weightOrthogonalLBP;
    this->weightHUE = weightHUE;
}