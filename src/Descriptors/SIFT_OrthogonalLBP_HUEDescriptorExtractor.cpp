#include "SIFT_OrthogonalLBP_HUEDescriptorExtractor.hpp"


PictureInformation SIFT_OrthogonalLBP_HUEDescriptorExtractor::computeHistogram(string pathToPicture)
{
    cv::Mat picture = imread(pathToPicture, CV_LOAD_IMAGE_GRAYSCALE);

    if (!picture.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    PictureInformation SIFTOrthogonalLbpPicture = this->SiftOrthogonalLbpExtractor->computeHistogram(pathToPicture);
    HueDescriptor hueDescriptor;
    PictureInformation huePicture = hueDescriptor.computeHistogram(pathToPicture);

    PictureInformation pi = PictureInformation(pathToPicture, getHistogramSize());

    for(int i = 0; i < SIFTOrthogonalLbpPicture.getHistogramSize(); ++i)
        pi.setValueAt(i, SIFTOrthogonalLbpPicture.getValueAt(i));

    for(int i = 0; i < huePicture.getHistogramSize(); ++i)
        pi.setValueAt(i + SIFTOrthogonalLbpPicture.getHistogramSize(), huePicture.getValueAt(i));
    return pi;
}

int SIFT_OrthogonalLBP_HUEDescriptorExtractor::getHistogramSize()
{
    return getDictionarySize() + HUE_HISTOGRAM_SIZE + ORTHOGONAL_LBP_HISTOGRAM_SIZE;
}

int SIFT_OrthogonalLBP_HUEDescriptorExtractor::getDictionarySize()
{
    return this->SiftOrthogonalLbpExtractor->getDictionarySize();
}


SIFT_OrthogonalLBP_HUEDescriptorExtractor::SIFT_OrthogonalLBP_HUEDescriptorExtractor(int dictionarySize, string pathToDatabase, string pathToDictionary)
{
    this->SiftOrthogonalLbpExtractor = new SIFT_OrthogonalLBPDescriptorExtractor(dictionarySize, pathToDatabase, pathToDictionary);
}

SIFT_OrthogonalLBP_HUEDescriptorExtractor::~SIFT_OrthogonalLBP_HUEDescriptorExtractor()
{
    delete this->SiftOrthogonalLbpExtractor;
}
