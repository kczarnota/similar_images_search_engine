#include "ResultVector.h"

ResultVector::ResultVector(int capacity, double mValue)
{
    this->capacity = capacity;
    this->freePositions = capacity;
    this->maxValue = mValue;
    this->table.resize(capacity);
    for(vector<pair<string, double>>::iterator it = this->table.begin(); it != this->table.end(); ++it)
        (*it).second = mValue;
}

bool ResultVector::tryAdd(pair<string, double> newPair)
{
    for(vector<pair<string, double>>::iterator it = this->table.begin(); it != this->table.end(); ++it)
    {
        if(newPair.second < (*it).second)
        {
            pair<string, double> copy = (*it);
            *it = newPair;
            rewriteRest(copy, ++it);
            return true;
        }
    }
    return false;
}

void ResultVector::rewriteRest(std::pair<string, double> pairToInsert, vector<pair<string, double>>::iterator it)
{
    pair<string, double> toMove;
    for(; it != this->table.end(); ++it)
    {
        toMove = *it;
        *it = pairToInsert;
        pairToInsert = toMove;
    }
}

pair<string, double> ResultVector::getPairAt(int index)
{
    return this->table[index];
}

void ResultVector::printTable()
{
    for(vector<pair<string, double>>::iterator it = this->table.begin(); it != this->table.end(); ++it)
        cout << (*it).first << " " <<  (*it).second << endl;
}