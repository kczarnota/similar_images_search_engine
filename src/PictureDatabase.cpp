#include "PictureDatabase.h"

PictureDatabase::PictureDatabase()
{

}

void PictureDatabase::addPicture(PictureInformation pi)
{
    this->database.push_back(pi);
}

PictureInformation PictureDatabase::getPicture(int i)
{
    return this->database[i];
}





