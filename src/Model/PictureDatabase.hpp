#ifndef BAGOFWORDS_PICTUREDATABASE_H
#define BAGOFWORDS_PICTUREDATABASE_H

#include "PictureInformation.hpp"
#include "../Dictionaries/VisualDictionary.hpp"

/*
 * Klasa przechowująca wektor obiektów PictureInforamtion opisujące obrazy
 */
class PictureDatabase
{
    friend class boost::serialization::access;
    std::vector<PictureInformation> database;
    string path;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & database;
    }
    int sizeOfDictionary;

public:
    PictureDatabase();
    PictureDatabase(int sizeOfDictionary);
    void addPicture(PictureInformation pi);
    PictureInformation getPicture(int i);
    int getSize();
};


#endif //BAGOFWORDS_PICTUREDATABASE_H
