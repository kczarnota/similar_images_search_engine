#ifndef BAGOFWORDS_PICTUREINFORMATION_H
#define BAGOFWORDS_PICTUREINFORMATION_H


#include <boost/serialization/vector.hpp>
#include <boost/serialization/access.hpp>

class PictureInformation
{
    friend class boost::serialization::access;
    std::vector<double> histogram;
    std::string pathToFile;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & histogram;
        ar & pathToFile;
    }

public:
    PictureInformation();
    PictureInformation(std::string filename);
    void add(double element);
    double getElement(int i);
    std::string getName();
};



#endif //BAGOFWORDS_PICTUREINFORMATION_H
