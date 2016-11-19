#ifndef BAGOFWORDS_SIFT_ORTHOGONALLBP_HUECOMPARATOR_HPP
#define BAGOFWORDS_SIFT_ORTHOGONALLBP_HUECOMPARATOR_HPP

#include "Comparator.hpp"

class SIFT_OrthogonalLBP_HUEComparator : public Comparator
{
private:
    int SIFTHistogramSize;
    const int ORTHOGONAL_LBP_HISTOGRAM_SIZE = 32;
    const int HUE_HISTOGRAM_SIZE = 362;
    double weightSIFT;
    double weightOrthogonalLBP;
public:
    SIFT_OrthogonalLBP_HUEComparator(int SIFTHistogramSize, double weightSIFT, double weightOrthogonalLBP,
                                     double weightHUE);

private:
    double weightHUE;

public:
    virtual double compare(const PictureInformation &p1, const PictureInformation &p2) const override;
};


#endif //BAGOFWORDS_SIFT_ORTHOGONALLBP_HUECOMPARATOR_HPP
