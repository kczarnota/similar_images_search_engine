#include "OrthogonalLBPDescriptor.hpp"

void OrthogonalLBPDescriptor::computeOrthogonalLBPfeatures(const Mat & image, Mat & lbpFeatures, const vector<KeyPoint> & keyPoints)
{
    for(KeyPoint p : keyPoints)
    {
        Mat dest;
        getRectSubPix(image, Size(10, 10), Point2f(p.pt.x, p.pt.y), dest);

        int flatNumber = 0;
        Mat currentFeatures = Mat(1, 128, CV_32FC1, Scalar(0));
        for(int r = 1; r < 9; ++r)
        {
            for (int c = 1; c < 9; ++c)
            {
                Scalar intensity = dest.at<uchar>(r, c);
                uchar mid = intensity.val[0];

                unsigned char numberOne = 0;
                unsigned char numberTwo = 0;

                //right middle
                intensity = dest.at<uchar>(r, c + 1);
                if(intensity.val[0] > mid)
                {
                    numberOne |= 1;
                }

                //bottom middle
                intensity = dest.at<uchar>(r + 1, c);
                if(intensity.val[0] > mid)
                {
                    numberOne |= 1 << 1;
                }

                //left middle
                intensity = dest.at<uchar>(r, c - 1);
                if(intensity.val[0] > mid)
                {
                    numberOne |= 1 << 2;
                }

                //right middle
                intensity = dest.at<uchar>(r - 1, c);
                if(intensity.val[0] > mid)
                {
                    numberOne |= 1 << 3;
                }

                //rigth bottom
                intensity = dest.at<uchar>(r + 1, c + 1);
                if(intensity.val[0] > mid)
                {
                    numberTwo |= 1;
                }


                //left bottom
                intensity = dest.at<uchar>(r + 1, c - 1);
                if(intensity.val[0] > mid)
                {
                    numberTwo |= 1 << 1;
                }


                //left top
                intensity = dest.at<uchar>(r - 1, c - 1);
                if(intensity.val[0] > mid)
                {
                    numberTwo |= 1 << 2;
                }


                //right top
                intensity = dest.at<uchar>(r - 1, c + 1);
                if(intensity.val[0] > mid)
                {
                    numberTwo |= 1 << 3;
                }


                currentFeatures.at<float>(0, flatNumber) = numberOne;
                flatNumber++;
                currentFeatures.at<float>(0, flatNumber) = numberTwo;
                flatNumber++;
            }
        }
        vconcat(currentFeatures, lbpFeatures, lbpFeatures);
    }
}