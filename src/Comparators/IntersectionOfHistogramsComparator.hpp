#ifndef BAGOFWORDS_INTERSECTIONOFHISTOGRAMSCOMPARATOR_HPP
#define BAGOFWORDS_INTERSECTIONOFHISTOGRAMSCOMPARATOR_HPP


#include "Comparator.hpp"
#include "../Model/PictureInformation.hpp"

class IntersectionOfHistogramsComparator : public Comparator
{
public:
    virtual double compare(const PictureInformation & p1, const PictureInformation & p2) const;
};


#endif //BAGOFWORDS_INTERSECTIONOFHISTOGRAMSCOMPARATOR_HPP
