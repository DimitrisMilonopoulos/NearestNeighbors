#include <iostream>
#include <fstream>
#include <sstream>

#include "fileReading.hpp"

using namespace std;

//Class used to handle the input items

Item::Item(string ID)
{
    itemID = ID;
    coordinates = new vector<int>;
}

Item::~Item()
{
    delete (coordinates);
}

string Item::getID()
{
    return itemID;
}

vector<int> *Item::getCoord()
{
    return coordinates;
}

void Item::addCoord(int coord)
{
    coordinates->push_back(coord);
}

//Class used to read the input files

vector<class Item> *Reading::readInputPoints(string FileLocation)
{
    ifstream infile(FileLocation);
    string line;
    //count the lines of the file
    int count = 0;
    ifstream file(FileLocation);
    while (getline(file, line))
        count++;

    cout << "Number of lines in file: " << count;

    while (getline(infile, line))
    {
        istringstream iss(line);
    }
}