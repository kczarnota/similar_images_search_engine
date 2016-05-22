#include <boost/regex.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include "BOW.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cout << "Usage: BagOfWords sizeOfDictionary pathToDatabase" << endl;
        exit(0);
    }

    BOW bow(atoi(argv[1]), argv[2]);
    bow.prepareDictionary();
    //bow.createDatabase(argv[2]);
    bow.loadDatabase();
    //bow.listDatabase();
    string pathToPic;
    cout << "Podaj nazwe pliku" << endl;
    cin >> pathToPic;
    while(pathToPic != "q")
    {
        string pic = bow.makeQuery(pathToPic);//("/home/konrad/Dokumenty/CLionProjects/BagOfWords/BazaDanych/autobus2.jpg");
        cout << pic << endl;
        cout << "Podaj nazwe pliku" << endl;
        cin >> pathToPic;
    }
    return 0;
}