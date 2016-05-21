#include "PictureInformation.h"

PictureInformation::PictureInformation()
{

}

PictureInformation::PictureInformation(std::string filename, int sizeOfDictionary)
{
    this->pathToFile = filename;
    this->histogram.resize(sizeOfDictionary);
}

/*
 * Dodaj jeden do liczby wystąpień danego słowa
 */
void PictureInformation::addOneAt(int index)
{
    (this->histogram)[index]++;
}


double PictureInformation::getValueAt(int index)
{
    return (this->histogram)[index];
}

std::string PictureInformation::getName()
{
    return this->pathToFile;
}

/*
 * Dzieli wartość wystąpień każdego słowa przez ilość wszystkich słów. Jest to niezbędne ponieważ obrazki mogą mieć
 * różną liczbę punktów kluczowych, a co za tym idzie są opisywane różną liczbą słów.
 */
void PictureInformation::normalize(int numberOfAllElements)
{
    for(int i = 0; i < this->histogram.size(); ++i)
    {
        if(this->histogram[i] != 0)
            this->histogram[i] /= numberOfAllElements;
    }
}
