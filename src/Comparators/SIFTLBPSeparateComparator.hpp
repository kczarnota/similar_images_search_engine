#ifndef BAGOFWORDS_SIFTLBPSEPARATECOMPARATOR_HPP
#define BAGOFWORDS_SIFTLBPSEPARATECOMPARATOR_HPP

#include "Comparator.hpp"

class SIFTLBPSeparateComparator : public Comparator
{
private:
    int SIFTHistogramSize;

public:
    SIFTLBPSeparateComparator(int SIFTDictionarySize);
    virtual double compare(const PictureInformation &p1, const PictureInformation &p2) const override;

};


#endif //BAGOFWORDS_SIFTLBPSEPARATECOMPARATOR_HPP
