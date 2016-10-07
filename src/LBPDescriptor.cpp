#include "LBPDescriptor.h"

void LBPDescriptor::computeLBPfeatures(Mat image, Mat lbpFeatures, vector<KeyPoint> keyPoints)
{
    int counter = 0;
    for(KeyPoint p : keyPoints)
    {
        Mat dest;
        getRectSubPix(image, Size(10, 10), Point2f(p.pt.x, p.pt.y), dest);

        int flatNumber = 0;
        for(int r = 1; r < 9; ++r)
        {
            for (int c = 1; c < 9; ++c)
            {
                Scalar intensity = dest.at<uchar>(r, c);
                uchar mid = intensity.val[0];

                unsigned char number = 0;

                //left middle
                intensity = dest.at<uchar>(r, c - 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 7;
                }

                //left bottom
                intensity = dest.at<uchar>(r + 1, c - 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 6;
                }

                //bottom middle
                intensity = dest.at<uchar>(r + 1, c);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 5;
                }

                //rigth bottom
                intensity = dest.at<uchar>(r + 1, c + 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 4;
                }

                //right middle
                intensity = dest.at<uchar>(r, c + 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 3;
                }

                //right top
                intensity = dest.at<uchar>(r - 1, c + 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 2;
                }

                //right middle
                intensity = dest.at<uchar>(r - 1, c);
                if(intensity.val[0] > mid)
                {
                    number |= 1 << 1;
                }

                //left top
                intensity = dest.at<uchar>(r - 1, c - 1);
                if(intensity.val[0] > mid)
                {
                    number |= 1;
                }

                lbpFeatures.at<float>(counter, flatNumber) = number;
                flatNumber++;
            }
        }
        counter++;
    }
}
