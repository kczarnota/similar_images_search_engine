#ifndef BAGOFWORDS_COMPARATOR_HPP
#define BAGOFWORDS_COMPARATOR_HPP


#include "../Model/PictureInformation.hpp"

class Comparator
{
protected:
    double siftWeight;
    double lbpWeight;
    double hueWeight;
public:
    virtual double compare(const PictureInformation & p1, const PictureInformation & p2) const = 0;
    virtual ~Comparator() {};
    void setSIFTWeight(double sW) {siftWeight = sW; };
    void setLBPWeight(double lW) {lbpWeight = lW; };
    void setHUEWeight(double hW) {hueWeight = hW; };
    double getSIFTWeight() const {return siftWeight;}
    double getLBPWeight() const {return lbpWeight;}
    double getHUEWeight() const {return hueWeight;}
};


#endif //BAGOFWORDS_COMPARATOR_HPP
