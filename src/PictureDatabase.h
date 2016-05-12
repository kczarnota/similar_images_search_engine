#ifndef BAGOFWORDS_PICTUREDATABASE_H
#define BAGOFWORDS_PICTUREDATABASE_H

#include "PictureInformation.h"

class PictureDatabase
{
    friend class boost::serialization::access;
    std::vector<PictureInformation> database;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & database;
    }

public:
    PictureDatabase();
    void addPicture(PictureInformation pi);
    PictureInformation getPicture(int i);

};


#endif //BAGOFWORDS_PICTUREDATABASE_H
