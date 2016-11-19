#include <iostream>
#include "LBPDescriptor.hpp"

void LBPDescriptor::computeLBPfeatures(const Mat & image, Mat & lbpFeatures, const vector<KeyPoint> & keyPoints)
{
    for(KeyPoint p : keyPoints)
    {
        Mat dest;
        getRectSubPix(image, Size(10, 10), Point2f(p.pt.x, p.pt.y), dest);

        int flatNumber = 0;
        Mat currentFeatures = Mat(1, PATCH_SIZE, CV_32FC1, Scalar(0));
        //For all 8 pixels around the center
        for(int r = 1; r < 9; ++r)
        {
            //Get one pixel value
            for (int c = 1; c < 9; ++c)
            {
                Scalar intensity = dest.at<uchar>(r, c);
                uchar mid = intensity.val[0];

                unsigned char number = 0;

                //right middle
                intensity = dest.at<uchar>(r, c + 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1;
                }

                //rigth bottom
                intensity = dest.at<uchar>(r + 1, c + 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 1;
                }

                //bottom middle
                intensity = dest.at<uchar>(r + 1, c);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 2;
                }

                //left bottom
                intensity = dest.at<uchar>(r + 1, c - 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 3;
                }

                //left middle
                intensity = dest.at<uchar>(r, c - 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 4;
                }

                //left top
                intensity = dest.at<uchar>(r - 1, c - 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 5;
                }

                //right middle
                intensity = dest.at<uchar>(r - 1, c);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 6;
                }


                //right top
                intensity = dest.at<uchar>(r - 1, c + 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 7;
                }


                currentFeatures.at<float>(0, flatNumber) = number;
                flatNumber++;
            }
        }
        vconcat(currentFeatures, lbpFeatures, lbpFeatures);
    }
}

PictureInformation LBPDescriptor::computeHistrogramForWholePicture(string pathToPicture)
{
    int values = 0;

    cv::Mat image = imread(pathToPicture, CV_LOAD_IMAGE_GRAYSCALE);

    if (!image.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    PictureInformation pictureInformation(pathToPicture, 256);
    for(int r = 1; r < image.rows - 1; ++r) //omit first and last row
    {
        for(int c = 1; c < image.cols - 1; ++c) //omit first and last column
        {
            Scalar intensity = image.at<uchar>(r, c);
            uchar mid = intensity.val[0];

            unsigned char number = 0;

            //right middle
            intensity = image.at<uchar>(r, c + 1);
            if(intensity.val[0] > mid)
            {
                number |= 1;
            }

            //rigth bottom
            intensity = image.at<uchar>(r + 1, c + 1);
            if(intensity.val[0] > mid)
            {
                number |= 1 << 1;
            }

            //bottom middle
            intensity = image.at<uchar>(r + 1, c);
            if(intensity.val[0] > mid)
            {
                number |= 1 << 2;
            }

            //left bottom
            intensity = image.at<uchar>(r + 1, c - 1);
            if(intensity.val[0] > mid)
            {
                number |= 1 << 3;
            }

            //left middle
            intensity = image.at<uchar>(r, c - 1);
            if(intensity.val[0] > mid)
            {
                number |= 1 << 4;
            }

            //left top
            intensity = image.at<uchar>(r - 1, c - 1);
            if(intensity.val[0] > mid)
            {
                number |= 1 << 5;
            }

            //right middle
            intensity = image.at<uchar>(r - 1, c);
            if(intensity.val[0] > mid)
            {
                number |= 1 << 6;
            }


            //right top
            intensity = image.at<uchar>(r - 1, c + 1);
            if(intensity.val[0] > mid)
            {
                number |= 1 << 7;
            }

            values++;
            pictureInformation.addOneAt(number);
        }
    }

    pictureInformation.normalize(values);
    return pictureInformation;
}

int LBPDescriptor::getHistogramSize()
{
    return HISTOGRAM_SIZE;
}

PictureInformation LBPDescriptor::computeHistogram(string pathToPicture)
{
    cv::Mat picture = imread(pathToPicture, CV_LOAD_IMAGE_GRAYSCALE);

    if (!picture.data)
    {
        cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    vector<KeyPoint> keyPoints;
    Ptr<SIFT> detector = SIFT::create();
    detector->detect(picture, keyPoints);
    int size = keyPoints.size();
    Mat features = Mat(0, PATCH_SIZE, CV_32FC1, Scalar(0));
    computeLBPfeatures(picture, features, keyPoints);

    PictureInformation pi = PictureInformation(pathToPicture, getHistogramSize());
    int values = 0;
    for(int i = 0; i < features.rows; ++i)
    {
        for(int j = 0; j < PATCH_SIZE; ++j)
        {
            pi.addOneAt(features.at<float>(i, j));
            ++values;
        }
    }

    pi.normalize(values);

    return pi;
}

int LBPDescriptor::getDictionarySize()
{
    return getHistogramSize();
}
