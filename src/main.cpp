#include <boost/regex.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include "Model/BOW.hpp"
#include "mainwindow.h"
#include <QApplication>

using namespace cv;
using namespace std;

void showManyImages(char* title, int nArgs, IplImage ** images);

int main(int argc, char** argv)
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
   /*	UNCOMMENT 
	if (argc != 5)
    {
        cout << "Usage: BagOfWords sizeOfDictionary pathToDatabase databaseName mode" << endl;
        exit(0);
    }


    BOW bow(atoi(argv[1]), argv[2], argv[3], argv[4]);
    bow.init();
    string pathToPic;
    int numberOfImagesToDisplay; */

   /* path p(argv[2]); ALLTESTS
    recursive_directory_iterator dir(p), end;
    double averagePrecision[9];
    double averageRecall[9];

    for(int i = 0; i < 9; ++i)
        averagePrecision[i] = 0.0;

    for(int i = 0; i < 9; ++i)
        averageRecall[i] = 0.0;

    int imagesQueried = 0;
    int wrongFirst = 0;
    while (dir != end)
    {
        file_status fs = status(dir->path());

        if (!is_directory(fs))
        {
            ResultVector res = bow.makeQuery(dir->path().string(), 90);

            if(res.getSize() == 0)
                continue;

            if(dir->path().string() != res.getPairAt(0).first)
            {
                wrongFirst++;
            }

            std::pair<double, double> p;
            p = bow.getPrecisionAndRecall(res, 10);
            averagePrecision[0] += p.first;
            averageRecall[0] += p.second;

           p = bow.getPrecisionAndRecall(res, 20);
            averagePrecision[1] += p.first;
            averageRecall[1] += p.second;

            p = bow.getPrecisionAndRecall(res, 30);
            averagePrecision[2] += p.first;
            averageRecall[2] += p.second;

            p = bow.getPrecisionAndRecall(res, 40);
            averagePrecision[3] += p.first;
            averageRecall[3] += p.second;

            p = bow.getPrecisionAndRecall(res, 50);
            averagePrecision[4] += p.first;
            averageRecall[4] += p.second;

            p = bow.getPrecisionAndRecall(res, 60);
            averagePrecision[5] += p.first;
            averageRecall[5] += p.second;

            p = bow.getPrecisionAndRecall(res, 70);
            averagePrecision[6] += p.first;
            averageRecall[6] += p.second;

            p = bow.getPrecisionAndRecall(res, 80);
            averagePrecision[7] += p.first;
            averageRecall[7] += p.second;

            p = bow.getPrecisionAndRecall(res, 90);
            averagePrecision[8] += p.first;
            averageRecall[8] += p.second;


            //cout << imagesQueried << " " << bow.getPrecision() << endl;

            ++imagesQueried;
        }

        ++dir;
    }

    for(int i = 0, j = 10; i < 9; ++i, j+= 10)
    {
        averagePrecision[i] /= imagesQueried;
        cout << "Average precison for: "<< j << "    " << averagePrecision[i] << endl;

        averageRecall[i] /= imagesQueried;
        cout << "Average recall for: "<< j << "    " << averageRecall[i] << endl;

        cout << "Wrong first " << wrongFirst << endl;
    }  */
	
	/* TEST WYBRANE

    cout << "Ile obrazow mam wyswietlic?" << endl;  
    cin >> numberOfImagesToDisplay;
    ++numberOfImagesToDisplay;
    cout << "Podaj nazwe pliku" << endl;
    cin >> pathToPic;
    while(pathToPic != "q")
    {
        ResultVector res = bow.makeQuery(pathToPic, numberOfImagesToDisplay);//("/home/konrad/Dokumenty/CLionProjects/BagOfWords/BazaDanych/autobus2.jpg");

        res.printTable();

        std::pair<double, double> p = bow.getPrecisionAndRecall(res, numberOfImagesToDisplay);
        cout << "Precision: " << p.first << ", recall: " << p.second << endl;
        //cout << "Precision: " << bow.getPrecision() << ", recall: " << bow.getRecall() << endl;

        IplImage ** images = new IplImage*[numberOfImagesToDisplay];

        for(int i = 0; i < numberOfImagesToDisplay; ++i)
        {
            images[i] = cvLoadImage(res.getPairAt(i).first.c_str());
        }

        showManyImages((char *)"Bag of Words", numberOfImagesToDisplay, images);
        delete images;
        cout << "Ile obrazow mam wyswietlic?" << endl;
        cin >> numberOfImagesToDisplay;
        ++numberOfImagesToDisplay;
        cout << "Podaj nazwe pliku" << endl;
        cin >> pathToPic;
    } */

    //bow.testPicture(10, 90, 10, 100);

    //return 0; UNCOMMENT
}

void showManyImages(char* title, int nArgs, IplImage ** images)
{
    // img - Used for getting the arguments
    IplImage *img;

    // [[DispImage]] - the image in which input images are to be copied
    IplImage *DispImage;

    int size;
    int i;
    int m, n;

    int x, y;
    // w - Maximum number of images in a row
    // h - Maximum number of images in a column
    int w, h;

    // scale - How much we have to resize the image
    float scale;
    int max;

    // If the number of arguments is lesser than 0 or greater than 12
    // return without displaying
    if (nArgs <= 0)
    {
        printf("Number of arguments too small....\n");
        return;
    }
    else if (nArgs > 12)
    {
        printf("Number of arguments too large....\n");
        return;
    }
        // Determine the size of the image,
        // and the number of rows/cols
        // from number of arguments
    else if (nArgs == 1)
    {
        w = h = 1;
        size = 300;
    }
    else if (nArgs == 2)
    {
        w = 2;
        h = 1;
        size = 300;
    }
    else if (nArgs == 3 || nArgs == 4)
    {
        w = 2;
        h = 2;
        size = 300;
    }
    else if (nArgs == 5 || nArgs == 6)
    {
        w = 3;
        h = 2;
        size = 200;
    }
    else if (nArgs == 7 || nArgs == 8)
    {
        w = 4;
        h = 2;
        size = 200;
    }
    else
    {
        w = 4;
        h = 3;
        size = 150;
    }

    // Create a new 3 channel image //[[ dispimage]]
    DispImage = cvCreateImage(cvSize(100 + size * w, 60 + size * h), 8, 3);


    // Loop for nArgs number of arguments
    for (i = 0, m = 20, n = 20; i < nArgs; i++, m += (20 + size))
    {

        // Get the Pointer to the IplImage
        img = images[i];

        // Check whether it is NULL or not
        // If it is NULL, release the image, and return
        if (img == 0)
        {
            printf("Invalid arguments");
            cvReleaseImage(&DispImage);
            return;
        }

        // Find the width and height of the image
        x = img->width;
        y = img->height;

        // Find whether height or width is greater in order to resize the image
        max = (x > y) ? x : y;

        // Find the scaling factor to resize the image
        scale = (float) ((float) max / size);

        // Used to Align the images
        if (i % w == 0 && m != 20)
        {
            m = 20;
            n += 20 + size;
        }

        // Set the image ROI to display the current image
        cvSetImageROI(DispImage, cvRect(m, n, (int) (x / scale), (int) (y / scale)));

        // Resize the input image and copy the it to the Single Big Image
        cvResize(img, DispImage);

        // Reset the ROI in order to display the next image
        cvResetImageROI(DispImage);
    }
    // Create a new window, and show the Single Big Image
    cvNamedWindow(title, 1);
    cvShowImage(title, DispImage);

    cvWaitKey();
    cvDestroyWindow(title);

    // Release the Image Memory
    cvReleaseImage(&DispImage);
}
