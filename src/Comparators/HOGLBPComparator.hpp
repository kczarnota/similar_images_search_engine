#ifndef BAGOFWORDS_HOGLBPCOMPARATOR_HPP
#define BAGOFWORDS_HOGLBPCOMPARATOR_HPP

#include "Comparator.hpp"

class HOGLBPComparator : public Comparator
{
private:
    int HOGHistogramSize;
    double weightHOG;
    double weightLBP;
public:
    HOGLBPComparator(int hogHistogramSize, double weightHog, double weightLBP);
    virtual double compare(const PictureInformation &p1, const PictureInformation &p2) const override;
};


#endif //BAGOFWORDS_HOGLBPCOMPARATOR_HPP
