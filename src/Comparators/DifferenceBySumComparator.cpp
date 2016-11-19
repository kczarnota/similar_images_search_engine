#include "DifferenceBySumComparator.hpp"

double DifferenceBySumComparator::compare(const PictureInformation &p1, const PictureInformation &p2) const
{
    int size = p1.getHistogramSize();
    double sum = 0;
    for(int i = 0; i < size; ++i)
    {
        double x = p1.getValueAt(i);
        double q = p2.getValueAt(i);
        if(x + q != 0)
            sum += std::abs(x - q)/(x + q);
    }
    return sum;
}