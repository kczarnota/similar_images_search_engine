#include "SIFTandLBPSeparateDescriptorExtractor.hpp"


PictureInformation SIFTandLBPSeparateDescriptorExtractor::computeHistogram(string pathToPicture)
{
    cv::Mat picture = imread(pathToPicture, CV_LOAD_IMAGE_GRAYSCALE);

    if (!picture.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    PictureInformation SIFTPicture = this->siftDescriptorExtractor->computeHistogram(pathToPicture);
    LBPDescriptor descriptorLBP;
    PictureInformation LBPPicture = descriptorLBP.computeHistogram(pathToPicture);

    PictureInformation pi = PictureInformation(pathToPicture, getHistogramSize());

    for(int i = 0; i < SIFTPicture.getHistogramSize(); ++i)
        pi.setValueAt(i, SIFTPicture.getValueAt(i));

    for(int i = 0; i < LBPPicture.getHistogramSize(); ++i)
        pi.setValueAt(i + SIFTPicture.getHistogramSize(), LBPPicture.getValueAt(i));

    return pi;
}


int SIFTandLBPSeparateDescriptorExtractor::getHistogramSize()
{
    return this->dictionarySize + LBP_HISTOGRAM_SIZE;
}

int SIFTandLBPSeparateDescriptorExtractor::getDictionarySize()
{
    return this->dictionarySize;
}

SIFTandLBPSeparateDescriptorExtractor::SIFTandLBPSeparateDescriptorExtractor(int dictionarySize, string pathToDatabase, string pathToDictionary)
{
    this->dictionarySize = dictionarySize;
    this->pathToDatabase = pathToDatabase;
    this->pathToDictionary = pathToDictionary;
    this->siftDescriptorExtractor = new SIFTDescriptorExtractor(this->dictionarySize, this->pathToDatabase, this->pathToDictionary);
}

SIFTandLBPSeparateDescriptorExtractor::~SIFTandLBPSeparateDescriptorExtractor()
{
    delete siftDescriptorExtractor;
}
