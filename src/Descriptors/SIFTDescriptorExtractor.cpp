#include "SIFTDescriptorExtractor.hpp"

void SIFTDescriptorExtractor::computeSIFTfeatures(const Mat &currentImage, Mat &features, vector<KeyPoint> & keyPoints)
{
    Ptr<SIFT> keyPointsDetector = SIFT::create();
    Ptr<SIFT> featureExtractor = SIFT::create();

    keyPointsDetector->detect(currentImage, keyPoints);
    featureExtractor->compute(currentImage, keyPoints, features);
}

SIFTDescriptorExtractor::SIFTDescriptorExtractor(int dictionarySize, string pathToDatabase, string pathToDictionary)
{
    visualDictionary = new SIFTDictionary(dictionarySize, pathToDatabase, pathToDictionary);
    visualDictionary->prepareDictionary();
}

SIFTDescriptorExtractor::~SIFTDescriptorExtractor()
{
    delete visualDictionary;
}

PictureInformation SIFTDescriptorExtractor::computeHistogram(string pathToPicture)
{
    vector<KeyPoint> keyPoints;
    cv::Mat picture = imread(pathToPicture, CV_LOAD_IMAGE_GRAYSCALE);

    if (!picture.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    Mat features = Mat(0, HISTOGRAM_SIZE, CV_32FC1, Scalar(0));
    SIFTDescriptorExtractor::computeSIFTfeatures(picture, features, keyPoints);
    return getHistogramBasedOnDictionary(pathToPicture, features);
}

int SIFTDescriptorExtractor::getDictionarySize()
{
    return visualDictionary->getSize();
}

int SIFTDescriptorExtractor::getHistogramSize()
{
    return HISTOGRAM_SIZE;
}
