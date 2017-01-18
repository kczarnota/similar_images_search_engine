#ifndef BAGOFWORDS_PICTUREINFORMATION_H
#define BAGOFWORDS_PICTUREINFORMATION_H


#include <boost/serialization/vector.hpp>
#include <boost/serialization/access.hpp>

/*
 * Class containing information about picture. It keeps histogram.
 */
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
    PictureInformation(std::string filename, int sizeOfDictionary);
    void addOneAt(int index);
    double getValueAt(int index) const;
    std::string getName();
    void normalize(int numberOfAllElements);
    int getHistogramSize() const;
    void setValueAt(int index, double value);
};



#endif //BAGOFWORDS_PICTUREINFORMATION_H
