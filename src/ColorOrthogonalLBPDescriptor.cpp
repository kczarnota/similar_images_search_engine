#include <iostream>
#include "ColorOrthogonalLBPDescriptor.hpp"

PictureInformation ColorOrthogonalLBPDescriptor::computeHistrogramForWholePicture(std::string pathToPicture)
{
    int values = 0;

    cv::Mat image = imread(pathToPicture, CV_LOAD_IMAGE_COLOR);

    if (!image.data)
    {
        std::cout << "Could not open or find the image" << std::endl;
        exit(-1);
    }

    PictureInformation pictureInformation(pathToPicture, HISTOGRAM_SIZE);

    for (int r = 1; r < image.rows - 1; ++r) //omit first and last row
    {
        for (int c = 1; c < image.cols - 1; ++c) //omit first and last column
        {
            Scalar intensity = image.at<uchar>(r, c);
            //OpenCV convention B, G, R
            uchar midB = intensity.val[0];
            uchar midG = intensity.val[1];
            uchar midR = intensity.val[2];

            unsigned char numberOneR = 0;
            unsigned char numberTwoR = 0;
            unsigned char numberOneG = 0;
            unsigned char numberTwoG = 0;
            unsigned char numberOneB = 0;
            unsigned char numberTwoB = 0;

            //right middle
            intensity = image.at<uchar>(r, c + 1);
            if (intensity.val[0] > midB)
            {
                numberOneB |= 1;
            }
            if (intensity.val[1] > midG)
            {
                numberOneG |= 1;
            }
            if (intensity.val[2] > midR)
            {
                numberOneR |= 1;
            }

            //bottom middle
            intensity = image.at<uchar>(r + 1, c);
            if (intensity.val[0] > midB)
            {
                numberOneB |= 1 << 1;
            }
            if (intensity.val[1] > midG)
            {
                numberOneG |= 1 << 1;
            }
            if (intensity.val[2] > midR)
            {
                numberOneR |= 1 << 1;
            }

            //left middle
            intensity = image.at<uchar>(r, c - 1);
            if (intensity.val[0] > midB)
            {
                numberOneB |= 1 << 2;
            }
            if (intensity.val[1] > midG)
            {
                numberOneG |= 1 << 2;
            }
            if (intensity.val[2] > midR)
            {
                numberOneR |= 1 << 2;
            }

            //right middle
            intensity = image.at<uchar>(r - 1, c);
            if (intensity.val[0] > midB)
            {
                numberOneB |= 1 << 3;
            }
            if (intensity.val[1] > midG)
            {
                numberOneG |= 1 << 3;
            }
            if (intensity.val[2] > midR)
            {
                numberOneR |= 1 << 3;
            }

            //rigth bottom
            intensity = image.at<uchar>(r + 1, c + 1);
            if (intensity.val[0] > midB)
            {
                numberTwoB |= 1;
            }
            if (intensity.val[1] > midG)
            {
                numberTwoG |= 1;
            }
            if (intensity.val[2] > midR)
            {
                numberTwoR |= 1;
            }


            //left bottom
            intensity = image.at<uchar>(r + 1, c - 1);
            if (intensity.val[0] > midB)
            {
                numberTwoB |= 1 << 1;
            }
            if (intensity.val[1] > midG)
            {
                numberTwoG |= 1 << 1;
            }
            if (intensity.val[2] > midR)
            {
                numberTwoR |= 1 << 1;
            }


            //left top
            intensity = image.at<uchar>(r - 1, c - 1);
            if (intensity.val[0] > midB)
            {
                numberTwoB |= 1 << 2;
            }
            if (intensity.val[1] > midG)
            {
                numberTwoG |= 1 << 2;
            }
            if (intensity.val[2] > midR)
            {
                numberTwoR |= 1 << 2;
            }


            //right top
            intensity = image.at<uchar>(r - 1, c + 1);
            if (intensity.val[0] > midB)
            {
                numberTwoB |= 1 << 3;
            }
            if (intensity.val[1] > midG)
            {
                numberTwoG |= 1 << 3;
            }
            if (intensity.val[2] > midR)
            {
                numberTwoR |= 1 << 3;
            }

            values += 2;
            pictureInformation.addOneAt(numberOneB);
            pictureInformation.addOneAt(numberTwoB + 16);
            pictureInformation.addOneAt(numberOneG + 32);
            pictureInformation.addOneAt(numberTwoG + 48);
            pictureInformation.addOneAt(numberOneR + 64);
            pictureInformation.addOneAt(numberTwoR + 80);
        }
    }

    pictureInformation.normalize(values);
    return pictureInformation;
}
