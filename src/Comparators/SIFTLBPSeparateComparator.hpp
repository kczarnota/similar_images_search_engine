#ifndef BAGOFWORDS_SIFTLBPSEPARATECOMPARATOR_HPP
#define BAGOFWORDS_SIFTLBPSEPARATECOMPARATOR_HPP

#include "Comparator.hpp"

class SIFTLBPSeparateComparator : public Comparator
{
private:
    int SIFTHistogramSize;
    double weightSIFT;
    double weightLBP;

public:
    SIFTLBPSeparateComparator(int SIFTDictionarySize, double weightSIFT,double weightLBP);
    virtual double compare(const PictureInformation &p1, const PictureInformation &p2) const override;

};


#endif //BAGOFWORDS_SIFTLBPSEPARATECOMPARATOR_HPP
