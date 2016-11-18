#ifndef BAGOFWORDS_BOW_H
#define BAGOFWORDS_BOW_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <cmath>
#include "PictureDatabase.h"
#include "VisualDictionary.h"
#include "ResultVector.h"
#include "SIFTDictionary.h"
#include "SIFTandLBPDictionary.h"
#include "LBPDescriptor.h"
#include "HOGDescriptorExtractor.hpp"
#include "HOGDictionary.hpp"
#include "OrthogonalLBPDescriptor.hpp"
#include "SIFTLBPDescriptorExtractor.hpp"
#include "ColorOrthogonalLBPDescriptor.hpp"
#include "HueDescriptor.hpp"
#include "Comparator.hpp"
#include "IntersectionOfHistogramsComparator.hpp"
#include "DifferenceBySumComparator.hpp"
#include "SIFTLBPSeparateComparator.hpp"
#include "SIFTandLBPSeparateDescriptorExtractor.hpp"
#include "SIFT_LBP_HUEDescriptorExtractor.hpp"
#include "SIFT_LBP_HUEComparator.hpp"


enum DistanceMode {IntersectionOfHistograms, DifferenceBySum};
/*
 * Główna klasa tworząca interfejs korzystania z metody BOW. Umożliwia stworzenie słownika(lub wczytanie go, jeśli
 * istnieje), utworzenie bazy obrazów, wczytanie obrazów do niej, zapisanie jej w pliku, odczyt z pliku oraz
 * umożliwia tworzenie zapytań.
 */
class BOW
{
private:
    const double DISTANCE_MAX_VALUE = 270.0;
    string pathToImages;
    string databasePath;
    string dictionaryPath = "../dictionary.xml";
    PictureDatabase * pictureDatabase;
    DistanceMode distanceMode;
    BasicDescriptor * descriptor;
    Comparator * comparator;

    void addPictureToDatabase(string pathToPicture);
    void saveDatabase();


public:
    //double comparePictureHistograms(PictureInformation p1, PictureInformation p2);
    //double compareDifferenceBySum(PictureInformation p1, PictureInformation p2);

    BOW(int sizeOfDictionary, string pathToImages, string databaseName, string mode);
    ~BOW();
    void init();
    void createDatabase();
    void updateDatabase(string pathToDatabase);
    void loadDatabase();
    ResultVector makeQuery(string pathToPicture, int resultNumber);
    std::pair<double, double> getPrecisionAndRecall(ResultVector vec, int numberOfAskedPictures);
    vector<string> splitString(string s);
    static void printMatrix(Mat matrix);
    string removeLastPathSegment(string path);
    int countImagesInCategory(string pathToCategoryDirectory);
};


#endif //BAGOFWORDS_BOW_H