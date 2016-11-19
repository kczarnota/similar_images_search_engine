#include "SIFT_OrthogonalLBPDescriptorExtractor.hpp"


PictureInformation SIFT_OrthogonalLBPDescriptorExtractor::computeHistogram(string pathToPicture)
{
    cv::Mat picture = imread(pathToPicture, CV_LOAD_IMAGE_GRAYSCALE);

    if (!picture.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    PictureInformation SIFTPicture = this->siftDescriptorExtractor->computeHistogram(pathToPicture);
    OrthogonalLBPDescriptor descriptorOrthogonalLBP;
    PictureInformation LBPPicture = descriptorOrthogonalLBP.computeHistogram(pathToPicture);

    PictureInformation pi = PictureInformation(pathToPicture, getHistogramSize());

    for(int i = 0; i < SIFTPicture.getHistogramSize(); ++i)
        pi.setValueAt(i, SIFTPicture.getValueAt(i));

    for(int i = 0; i < LBPPicture.getHistogramSize(); ++i)
        pi.setValueAt(i + SIFTPicture.getHistogramSize(), LBPPicture.getValueAt(i));

    return pi;
}


int SIFT_OrthogonalLBPDescriptorExtractor::getHistogramSize()
{
    return this->siftDescriptorExtractor->getDictionarySize() + ORTHOGONAL_LBP_HISTOGRAM_SIZE;
}

int SIFT_OrthogonalLBPDescriptorExtractor::getDictionarySize()
{
    return this->siftDescriptorExtractor->getDictionarySize();
}

SIFT_OrthogonalLBPDescriptorExtractor::SIFT_OrthogonalLBPDescriptorExtractor(int dictionarySize, string pathToDatabase, string pathToDictionary)
{
    this->siftDescriptorExtractor = new SIFTDescriptorExtractor(dictionarySize, pathToDatabase, pathToDictionary);
}

SIFT_OrthogonalLBPDescriptorExtractor::~SIFT_OrthogonalLBPDescriptorExtractor()
{
    delete this->siftDescriptorExtractor;
}
