#ifndef BAGOFWORDS_BOW_H
#define BAGOFWORDS_BOW_H

#include "PictureDatabase.h"
#include "VisualDictionary.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

/*
 * Główna klasa tworząca interfejs korzystania z metody BOW. Umożliwia stworzenie słownika(lub wczytanie go, jeśli
 * istnieje), utworzenie bazy obrazów, wczytanie obrazów do niej, zapisanie jej w pliku, odczyt z pliku oraz
 * umożliwia tworzenie zapytań.
 */
class BOW
{
private:
    VisualDictionary * visualDictionary;
    PictureDatabase * pictureDatabase;
    void addPictureToDatabase(string pathToPicture);
    void saveDatabase();
    PictureInformation computeHistogram(string pathToPicture);
    double comparePictureHistograms(PictureInformation p1, PictureInformation p2);

public:
    BOW(int sizeOfDictionary, string pathToDatabase);
    ~BOW();
    void prepareDictionary();
    void createDatabase(string pathToDatabase);
    void updateDatabase(string pathToDatabase);
    void loadDatabase();
    void listDatabase();
    string makeQuery(string pathToPicture);
};


#endif //BAGOFWORDS_BOW_H
