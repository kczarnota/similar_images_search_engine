#ifndef BAGOFWORDS_RESULTVECTOR_H
#define BAGOFWORDS_RESULTVECTOR_H

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

/*
 * Klasa pomocnicza służąca do wyodrębnienia n najbardziej podobnych obrazów.
 */
class ResultVector
{
private:
    int capacity;
    int freePositions;
    double maxValue;
    vector<pair<string, double>> table;

public:
    ResultVector(int capacity, double mValue);
    bool tryAdd(std::pair<string, double> newPair);
    void rewriteRest(std::pair<string, double> pairToInsert, vector<pair<string, double>>::iterator it);
    pair<string, double> getPairAt(int index);
    void printTable();
    int getSize();

};


#endif //BAGOFWORDS_RESULTVECTOR_H
