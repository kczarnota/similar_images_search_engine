#ifndef BAGOFWORDS_BOW_H
#define BAGOFWORDS_BOW_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <cmath>
#include "PictureDatabase.hpp"
#include "../Dictionaries/VisualDictionary.hpp"
#include "ResultVector.hpp"
#include "../Dictionaries/SIFTDictionary.hpp"
#include "../Dictionaries/SIFTandLBPDictionary.hpp"
#include "../Descriptors/LBPDescriptor.hpp"
#include "../Descriptors/HOGDescriptorExtractor.hpp"
#include "../Dictionaries/HOGDictionary.hpp"
#include "../Descriptors/OrthogonalLBPDescriptor.hpp"
#include "../Descriptors/SIFTLBPDescriptorExtractor.hpp"
#include "../Descriptors/ColorOrthogonalLBPDescriptor.hpp"
#include "../Descriptors/HueDescriptor.hpp"
#include "../Comparators/Comparator.hpp"
#include "../Comparators/IntersectionOfHistogramsComparator.hpp"
#include "../Comparators/DifferenceBySumComparator.hpp"
#include "../Comparators/SIFTLBPSeparateComparator.hpp"
#include "../Descriptors/SIFTandLBPSeparateDescriptorExtractor.hpp"
#include "../Descriptors/SIFT_LBP_HUEDescriptorExtractor.hpp"
#include "../Comparators/SIFT_LBP_HUEComparator.hpp"
#include "../Comparators/SIFT_OrthogonalLBPComparator.hpp"
#include "../Descriptors/SIFT_OrthogonalLBPDescriptorExtractor.hpp"
#include "../Descriptors/SIFT_OrthogonalLBP_HUEDescriptorExtractor.hpp"
#include "../Comparators/SIFT_OrthogonalLBP_HUEComparator.hpp"
#include "../Descriptors/HOGLBPDescriptor.hpp"
#include "../Comparators/HOGLBPComparator.hpp"


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
    PictureDatabase * pictureDatabase = nullptr;
    DistanceMode distanceMode;
    BasicDescriptor * descriptor= nullptr;
    Comparator * comparator = nullptr;
    bool databaseReady;

    void addPictureToDatabase(string pathToPicture);
    void saveDatabase();


public:
    //double comparePictureHistograms(PictureInformation p1, PictureInformation p2);
    //double compareDifferenceBySum(PictureInformation p1, PictureInformation p2);

    BOW(int sizeOfDictionary, string pathToImages, string databaseName, string mode, double sW, double lW, double hW);
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
    static string getNLastPathSegments(string path, int n);
    int countImagesInCategory(string pathToCategoryDirectory);
    void setSIFTWeight(double sW);
    void setLBPWeight(double lW);
    void setHUEWeight(double hW);
    static int countFiles(string path);
    bool isDictionaryReady();
    bool isDatabaseReady();
};


#endif //BAGOFWORDS_BOW_H