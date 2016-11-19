#include "IntersectionOfHistogramsComparator.hpp"

double IntersectionOfHistogramsComparator::compare(const PictureInformation &p1, const PictureInformation &p2) const
{
    double distance = 0.0, sumOfMinElements = 0.0;
    int size = p1.getHistogramSize();

    for(int i = 0; i < size; ++i)
        sumOfMinElements += std::min(p1.getValueAt(i), p2.getValueAt(i));

    distance = 1 - sumOfMinElements;
    return distance;
}
