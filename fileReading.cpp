#include <iostream>
#include <fstream>
#include <sstream>

#include "fileReading.hpp"

using namespace std;

//Class used to handle the input Points

Point::Point(string ID, int *coord, int siz)
{
    PointID = ID;
    coordinates = coord;
    size = siz;
}

Point::~Point()
{
    delete[](coordinates);
}

string Point::getID()
{
    return PointID;
}

int Point::getSize()
{
    return size;
}

//Class used to read the input files

class Point **Reading::readPoints(string FileLocation, int *tableSize)
{
    ifstream infile(FileLocation);
    string line;
    //count the lines of the file
    int count = 0;
    int columns = 0;
    int x;
    ifstream file(FileLocation);
    if (getline(file, line))
    {
        count++;
        //count the columns
        istringstream buffer(line);
        while (buffer >> x)
        {
            columns++;
        }
        columns--; //exclude the Point name
    }
    while (getline(file, line))
        count++;

    cout << "Number of lines in file: " << count << '\n';
    cout << "Number of dimensions per point: " << columns << '\n';

    //construct the table of Points
    class Point **table = new class Point *[count];
    int j = 0;
    while (getline(infile, line))
    {
        istringstream iss(line);
        //get the name
        string name;
        string buff;
        int *coord = new int[columns];
        iss >> name;
        for (int i = 0; i < columns; i++)
        {
            iss >> coord[i];
        }
        class Point *newPoint = new class Point(name, coord, columns);
        table[j] = newPoint;
        j++;
    }
    // for (int i = 0; i < count; i++)
    // {
    //     delete (table[i]);
    // }
    // delete[](table);
    *tableSize = count;
    return table;
}