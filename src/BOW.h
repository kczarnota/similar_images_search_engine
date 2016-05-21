#ifndef BAGOFWORDS_BOW_H
#define BAGOFWORDS_BOW_H

#include "PictureDatabase.h"
#include "VisualDictionary.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


class BOW
{
private:
    VisualDictionary * visualDictionary;
    PictureDatabase * pictureDatabase;
    void addPictureToDatabase(string pathToPicture);
    void saveDatabase();

public:
    BOW(int sizeOfDictionary, string pathToDatabase);
    ~BOW();
    void prepareDictionary();
    void createDatabase(string pathToDatabase);
    void updateDatabase(string pathToDatabase);
    void loadDatabase();
    void listDatabase();
};


#endif //BAGOFWORDS_BOW_H
