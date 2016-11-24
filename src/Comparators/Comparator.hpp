#ifndef BAGOFWORDS_COMPARATOR_HPP
#define BAGOFWORDS_COMPARATOR_HPP


#include "../Model/PictureInformation.hpp"

class Comparator
{
public:
    virtual double compare(const PictureInformation & p1, const PictureInformation & p2) const = 0;
    virtual ~Comparator() {};
};


#endif //BAGOFWORDS_COMPARATOR_HPP
