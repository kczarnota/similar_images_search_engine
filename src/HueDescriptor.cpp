#include "HueDescriptor.hpp"

void HueDescriptor::computeHueFeatures(const Mat &image, Mat &hueFeatures, const vector<KeyPoint> &keyPoints)
{
    for(KeyPoint p : keyPoints)
    {
        Mat dest;
        getRectSubPix(image, Size(20, 20), Point2f(p.pt.x, p.pt.y), dest);

        int flatNumber = 0;
        Mat currentFeatures = Mat(1, PATCH_SIZE, CV_32FC1, Scalar(0));
        for(int r = 0; r < 19; ++r)
        {
            for (int c = 0; c < 19; ++c)
            {
                //OPENCV keeps h in range 0 - 179 to fit uchar; i will multiply it by 2, so it's in 0 - 358
                Vec3b hsv = dest.at<Vec3b>(r, c);
                float h = hsv.val[0];
                float s = hsv.val[1];

                currentFeatures.at<float>(0, flatNumber) = h*2;
                flatNumber++;
                currentFeatures.at<float>(0, flatNumber) = s;
                flatNumber++;
            }
        }
        vconcat(currentFeatures, hueFeatures, hueFeatures);
    }
}

PictureInformation HueDescriptor::computeHistogram(string pathToPicture)
{
    int values = 0;

    cv::Mat imageBGR = imread(pathToPicture, CV_LOAD_IMAGE_COLOR);
    cv::Mat image;

    if (!imageBGR.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    Ptr<SIFT> keyPointsDetector = SIFT::create();
    vector<KeyPoint> keyPoints;
    keyPointsDetector->detect(imageBGR, keyPoints);
    int s = keyPoints.size();
    cvtColor(imageBGR, image, COLOR_BGR2HSV);
    Mat features = Mat(1, PATCH_SIZE, CV_32FC1, Scalar(0));
    computeHueFeatures(image, features, keyPoints);

    PictureInformation pi(pathToPicture, HISTOGRAM_SIZE);

    for(int i = 0; i < features.rows; ++i)
    {
        for(int j = 0; j < PATCH_SIZE; ++j)
        {
            pi.addOneAt(features.at<float>(i, j));
            ++j;
            if(features.at<float>(i, j) < 128)
                pi.addOneAt(360);
            else
                pi.addOneAt(361);


            values+=2;
        }
    }
    pi.normalize(values);

    return pi;
}

int HueDescriptor::getHistogramSize()
{
    return HISTOGRAM_SIZE;
}

int HueDescriptor::getDictionarySize()
{
    return getHistogramSize();
}

