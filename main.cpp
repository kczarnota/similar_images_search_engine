#include <boost/regex.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include "VisualDictionary.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cout << "Usage: BagOfWords sizeOfDictionary pathToDatabase" << endl;
        exit(0);
    }

    VisualDictionary * visualDictionary = new VisualDictionary(atoi(argv[1]), argv[2]);
    visualDictionary->initializeDictionary();


    return 0;
}

/*
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], IMREAD_COLOR); // Read the file

	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}
*/