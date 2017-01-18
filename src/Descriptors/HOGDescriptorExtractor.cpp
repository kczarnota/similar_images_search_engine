#include "HOGDescriptorExtractor.hpp"

void HOGDescriptorExtractor::computeHOGfeatures(const Mat &currentImage, Mat &features)
{
    HOGDescriptor * featureExtractor;
    vector<Point> keyPoints;
    vector<float> descriptors;

    int alignedWidth = currentImage.cols - currentImage.cols % 8;
    int alignedHeight = currentImage.rows - currentImage.rows %8;
    int blockSize = 8;
    int blockStride = 8;
    int cellSize = 4;
    int nBins = 9;

    Mat currentFeatures = Mat(1, HISTOGRAM_SIZE, CV_32FC1, Scalar(0));

    featureExtractor = new HOGDescriptor(Size(alignedWidth, alignedHeight)
            , Size(blockSize, blockSize), Size(blockStride, blockStride), Size(cellSize, cellSize), nBins);

    featureExtractor->compute(currentImage, descriptors, Size(0, 0), Size(0, 0), keyPoints);

    int blocksInImage = (alignedWidth / 8) * (alignedHeight / 8);
    int descNumber = 0;
    for(int i = 0; i < blocksInImage; ++i)
    {
        for(int j = 0; j < 36; ++j, descNumber++)
        {
            currentFeatures.at<float>(0, j) = descriptors[descNumber];
        }
        //Add new features
        vconcat(currentFeatures, features, features);
    }

    delete featureExtractor;
}

PictureInformation HOGDescriptorExtractor::computeHistogram(string pathToPicture)
{
    cv::Mat picture = imread(pathToPicture, CV_LOAD_IMAGE_GRAYSCALE);

    if (!picture.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    Mat features = Mat(0, HISTOGRAM_SIZE, CV_32FC1, Scalar(0));
    HOGDescriptorExtractor::computeHOGfeatures(picture, features);
    return getHistogramBasedOnDictionary(pathToPicture, features);
}

HOGDescriptorExtractor::HOGDescriptorExtractor(int dictionarySize, string pathToDatabase, string pathToDictionary)
{
    this->visualDictionary = new HOGDictionary(dictionarySize, pathToDatabase, pathToDictionary);
    this->visualDictionary->prepareDictionary();
}

HOGDescriptorExtractor::~HOGDescriptorExtractor()
{
    delete  this->visualDictionary;
}

int HOGDescriptorExtractor::getDictionarySize()
{
    return visualDictionary->getSize();
}

int HOGDescriptorExtractor::getHistogramSize()
{
    return HISTOGRAM_SIZE;
}
