#include "PictureDatabase.hpp"

PictureDatabase::PictureDatabase()
{

}

PictureDatabase::PictureDatabase(int sizeOfDictionary)
{
    this->sizeOfDictionary = sizeOfDictionary;
}

void PictureDatabase::addPicture(PictureInformation pi)
{
    this->database.push_back(pi);
}

PictureInformation PictureDatabase::getPicture(int i)
{
    return this->database[i];
}

int PictureDatabase::getSize()
{
    return (int)this->database.size();
}