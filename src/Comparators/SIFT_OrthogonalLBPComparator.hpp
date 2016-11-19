#ifndef BAGOFWORDS_SIFT_ORTHOGONALLBPCOMPARATOR_HPP
#define BAGOFWORDS_SIFT_ORTHOGONALLBPCOMPARATOR_HPP

#include "Comparator.hpp"

class SIFT_OrthogonalLBPComparator : public Comparator
{
private:
    int SIFTHistogramSize;
    double weightSIFT;
    double weightOrthogonalLBP;

public:
    SIFT_OrthogonalLBPComparator(int SIFTHistogramSize, double weightSIFT, double weightOrthogonalLBP);
    virtual double compare(const PictureInformation &p1, const PictureInformation &p2) const override;
};


#endif //BAGOFWORDS_SIFT_ORTHOGONALLBPCOMPARATOR_HPP
