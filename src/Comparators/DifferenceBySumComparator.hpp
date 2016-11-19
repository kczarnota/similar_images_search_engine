#ifndef BAGOFWORDS_DIFFERENCEBYSUMCOMPARATOR_HPP
#define BAGOFWORDS_DIFFERENCEBYSUMCOMPARATOR_HPP


#include "Comparator.hpp"

class DifferenceBySumComparator : public Comparator
{
    virtual double compare(const PictureInformation & p1, const PictureInformation & p2) const;
};


#endif //BAGOFWORDS_DIFFERENCEBYSUMCOMPARATOR_HPP
