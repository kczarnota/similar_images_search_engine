#ifndef BAGOFWORDS_HOGLBPCOMPARATOR_HPP
#define BAGOFWORDS_HOGLBPCOMPARATOR_HPP

#include "Comparator.hpp"

class HOGLBPComparator : public Comparator
{
private:
    int HOGHistogramSize;
public:
    HOGLBPComparator(int hogHistogramSize);
    virtual double compare(const PictureInformation &p1, const PictureInformation &p2) const override;
};


#endif //BAGOFWORDS_HOGLBPCOMPARATOR_HPP
