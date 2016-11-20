#include "HOGLBPDescriptor.hpp"


PictureInformation HOGLBPDescriptor::computeHistogram(string pathToPicture)
{
    cv::Mat picture = imread(pathToPicture, CV_LOAD_IMAGE_GRAYSCALE);

    if (!picture.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    PictureInformation HOGPicture = this->hogDescriptorExtractor->computeHistogram(pathToPicture);
    LBPDescriptor descriptorLBP;
    PictureInformation LBPPicture = descriptorLBP.computeHistrogramForWholePicture(pathToPicture);

    PictureInformation pi = PictureInformation(pathToPicture, getHistogramSize());

    for(int i = 0; i < HOGPicture.getHistogramSize(); ++i)
        pi.setValueAt(i, HOGPicture.getValueAt(i));

    for(int i = 0; i < LBPPicture.getHistogramSize(); ++i)
        pi.setValueAt(i + HOGPicture.getHistogramSize(), LBPPicture.getValueAt(i));

    return pi;
}

HOGLBPDescriptor::HOGLBPDescriptor(int dictionarySize, string pathToDatabase, string pathToDictionary)
{
    this->hogDescriptorExtractor = new HOGDescriptorExtractor(dictionarySize, pathToDatabase, pathToDictionary);
}

HOGLBPDescriptor::~HOGLBPDescriptor()
{
    delete this->hogDescriptorExtractor;
}

int HOGLBPDescriptor::getHistogramSize()
{
    return getDictionarySize() + LBP_HISTOGRAM_SIZE;
}

int HOGLBPDescriptor::getDictionarySize()
{
    return this->hogDescriptorExtractor->getDictionarySize();
}