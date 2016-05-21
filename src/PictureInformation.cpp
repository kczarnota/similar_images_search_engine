#include "PictureInformation.h"

PictureInformation::PictureInformation(std::string filename, int sizeOfDictionary)
{
    this->pathToFile = filename;
    this->histogram.resize(sizeOfDictionary);
}

void PictureInformation::addOneAt(int index)
{
    (this->histogram)[index]++;
}

PictureInformation::PictureInformation()
{

}

double PictureInformation::getValueAt(int index)
{
    return (this->histogram)[index];
}

std::string PictureInformation::getName()
{
    return this->pathToFile;
}

void PictureInformation::normalize(int numberOfAllElements)
{
    for(int i = 0; i < this->histogram.size(); ++i)
    {
        if(this->histogram[i] != 0)
            this->histogram[i] /= numberOfAllElements;
    }
}

PictureInformation &PictureInformation::operator=(PictureInformation pi)
{
  /*  this->value = token.value;
    this->type = token.type;
    this->position = token.position; */
    return *this;
}




