#ifndef BAGOFWORDS_COMPARATOR_HPP
#define BAGOFWORDS_COMPARATOR_HPP


#include "PictureInformation.h"

class Comparator
{
public:
    virtual double compare(const PictureInformation & p1, const PictureInformation & p2) const = 0;
};


#endif //BAGOFWORDS_COMPARATOR_HPP
