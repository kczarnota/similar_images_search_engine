#include "SIFTLBPDescriptorExtractor.hpp"
#include "SIFTDescriptorExtractor.hpp"
#include "LBPDescriptor.h"

SIFTLBPDescriptorExtractor::SIFTLBPDescriptorExtractor(int dictionarySize, string pathToDatabase,
                                                       string pathToDictionary)
{
    visualDictionary = new SIFTandLBPDictionary(dictionarySize, pathToDatabase, pathToDictionary);
    visualDictionary->prepareDictionary();
}

SIFTLBPDescriptorExtractor::~SIFTLBPDescriptorExtractor()
{
    delete visualDictionary;
}

void SIFTLBPDescriptorExtractor::computeSIFTandLBPfeatures(const Mat &image, Mat & features)
{
    vector<KeyPoint> keyPoints;
    Mat lbpFeatures = Mat(0, 64, CV_32FC1, Scalar(0));
    Mat onlySIFT = Mat(0, 128, CV_32FC1, Scalar(0));
    SIFTDescriptorExtractor::computeSIFTfeatures(image, onlySIFT, keyPoints);
    LBPDescriptor::computeLBPfeatures(image, lbpFeatures, keyPoints);
    features = Mat(onlySIFT.rows, HISTOGRAM_SIZE, CV_32FC1, Scalar(0));

    for (int i = 0; i < features.rows; ++i)
    {
        for (int j = 0; j < 192; ++j)
        {
            if(j < 128)
            {
                features.at<float>(i, j) = onlySIFT.at<float>(i, j);
            }
            else
            {
                features.at<float>(i, j) = lbpFeatures.at<float>(i, j % 64);
            }
        }
    }
}

PictureInformation SIFTLBPDescriptorExtractor::computeHistogram(string pathToPicture)
{
    cv::Mat picture = imread(pathToPicture, CV_LOAD_IMAGE_GRAYSCALE);

    if (!picture.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    Mat features = Mat(0, HISTOGRAM_SIZE, CV_32FC1, Scalar(0));
    SIFTLBPDescriptorExtractor::computeSIFTandLBPfeatures(picture, features);
    return getHistogramBasedOnDictionary(pathToPicture, features);
}

int SIFTLBPDescriptorExtractor::getDictionarySize()
{
    return visualDictionary->getSize();
}

int SIFTLBPDescriptorExtractor::getHistogramSize()
{
    return HISTOGRAM_SIZE;
}