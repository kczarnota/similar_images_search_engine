#include "DescriptorUsingDictionary.hpp"

PictureInformation DescriptorUsingDictionary::getHistogramBasedOnDictionary(string pathToPicture, Mat &features)
{
    PictureInformation pictureInformation(pathToPicture, visualDictionary->getSize());

    Mat currentRow(1, getHistogramSize(), CV_32FC1, Scalar(0));
    Mat currentWord(1, getHistogramSize(), CV_32FC1, Scalar(0));
    Mat difference(1, getHistogramSize(), CV_32FC1, Scalar(0));

    std::cout << features.rows << std::endl;

    int i, j;
    for(i = 0; i < features.rows; ++i)
    {
        int minSumIndex = 0;
        float minSum = -1;
        features.row(i).copyTo(currentRow.row(0));
        for(j = 0; j < visualDictionary->getSize(); ++j)
        {
            float currentSum = 0;
            visualDictionary->getWord(j).copyTo(currentWord.row(0));
            absdiff(currentRow, currentWord, difference);

            for(int k = 0; k < getHistogramSize(); ++k)
                currentSum += difference.at<float>(0, k);

            if(minSum == -1 || currentSum < minSum)
            {
                minSum = currentSum;
                minSumIndex = j;
            }
        }
        pictureInformation.addOneAt(minSumIndex);
    }

    pictureInformation.normalize(features.rows);

    return pictureInformation;
}