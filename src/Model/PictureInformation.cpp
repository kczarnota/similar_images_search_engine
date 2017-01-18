#include "PictureInformation.hpp"

PictureInformation::PictureInformation()
{

}

PictureInformation::PictureInformation(std::string filename, int sizeOfDictionary)
{
    this->pathToFile = filename;
    this->histogram.resize(sizeOfDictionary);
}

/*
 * Add one to words occurrence
 */
void PictureInformation::addOneAt(int index)
{
    (this->histogram)[index]++;
}

/*
 * Get words count in histogram
 */
double PictureInformation::getValueAt(int index) const
{
    return (this->histogram)[index];
}

/*
 * Returns path to file
 */
std::string PictureInformation::getName()
{
    return this->pathToFile;
}

/*
 * Normalizes histogram
 */
void PictureInformation::normalize(int numberOfAllElements)
{
    for(int i = 0; i < this->histogram.size(); ++i)
    {
        this->histogram[i] /= numberOfAllElements;
    }
}

int PictureInformation::getHistogramSize() const
{
    return this->histogram.size();
}

void PictureInformation::setValueAt(int index, double value)
{
    (this->histogram[index]) = value;
}
