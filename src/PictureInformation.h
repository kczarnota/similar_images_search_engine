#ifndef BAGOFWORDS_PICTUREINFORMATION_H
#define BAGOFWORDS_PICTUREINFORMATION_H


#include <boost/serialization/vector.hpp>
#include <boost/serialization/access.hpp>

/*
 * Klasa przechowująca informacje o obrazie. Zawiera histogram słów utworzony na podstawie słownika.
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
};



#endif //BAGOFWORDS_PICTUREINFORMATION_H
