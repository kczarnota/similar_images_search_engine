#include "PictureInformation.h"

PictureInformation::PictureInformation(std::string filename)
{
    this->pathToFile = filename;
}

void PictureInformation::add(double element)
{
    this->histogram.push_back(element);
}

PictureInformation::PictureInformation()
{

}

double PictureInformation::getElement(int i)
{
    return this->histogram[i];
}

std::string PictureInformation::getName()
{
    return this->pathToFile;
}
