#include "SIFT_LBP_HUEDescriptorExtractor.hpp"

PictureInformation SIFT_LBP_HUEDescriptorExtractor::computeHistogram(string pathToPicture)
{
    cv::Mat picture = imread(pathToPicture, CV_LOAD_IMAGE_GRAYSCALE);

    if (!picture.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    PictureInformation SIFTLbpPicture = this->SiftLbpExtractor->computeHistogram(pathToPicture);
    HueDescriptor hueDescriptor;
    PictureInformation huePicture = hueDescriptor.computeHistogram(pathToPicture);

    PictureInformation pi = PictureInformation(pathToPicture, getHistogramSize());

    for(int i = 0; i < SIFTLbpPicture.getHistogramSize(); ++i)
        pi.setValueAt(i, SIFTLbpPicture.getValueAt(i));

    for(int i = 0; i < huePicture.getHistogramSize(); ++i)
        pi.setValueAt(i + SIFTLbpPicture.getHistogramSize(), huePicture.getValueAt(i));
    return pi;
}

SIFT_LBP_HUEDescriptorExtractor::SIFT_LBP_HUEDescriptorExtractor(int dictionarySize, const string &pathToDatabase, const string &pathToDictionary)
{
    this->SiftLbpExtractor = new SIFTandLBPSeparateDescriptorExtractor(dictionarySize, pathToDatabase, pathToDictionary);
}

SIFT_LBP_HUEDescriptorExtractor::~SIFT_LBP_HUEDescriptorExtractor()
{
    delete this->SiftLbpExtractor;
}

int SIFT_LBP_HUEDescriptorExtractor::getHistogramSize()
{
    return this->SiftLbpExtractor->getDictionarySize() + LBP_HISTOGRAM_SIZE + HUE_HISTOGRAM_SIZE;
}

int SIFT_LBP_HUEDescriptorExtractor::getDictionarySize()
{
    return this->SiftLbpExtractor->getDictionarySize();
}