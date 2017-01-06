#ifndef BAGOFWORDS_SIFT_LBP_HUECOMPARATOR_HPP
#define BAGOFWORDS_SIFT_LBP_HUECOMPARATOR_HPP

#include "Comparator.hpp"

class SIFT_LBP_HUEComparator : public Comparator
{
private:
    int SIFTHistogramSize;
    const int LBP_HISTOGRAM_SIZE = 256;
    const int HUE_HISTOGRAM_SIZE = 362;


public:
    SIFT_LBP_HUEComparator(int SIFTDictionarySize);
    virtual double compare(const PictureInformation &p1, const PictureInformation &p2) const override;

};

#endif //BAGOFWORDS_SIFT_LBP_HUECOMPARATOR_HPP
