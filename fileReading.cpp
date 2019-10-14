#include <iostream>
#include <fstream>
#include <sstream>

#include "point.hpp"
#include "fileReading.hpp"

using namespace std;

//Class used to read the input files

vector<class Point *> *Reading::readPoints(string FileLocation)
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

    cout << "Number of lines in file: " << count << endl;
    cout << "Number of dimensions per point: " << columns << endl;

    //construct the table of Points
    vector<class Point *> *table = new vector<class Point *>;
    table->reserve(count);
    int j = 0;
    while (getline(infile, line))
    {
        istringstream iss(line);
        //get the name
        string name;
        string buff;
        double *coord = new double[columns];
        iss >> name;
        for (int i = 0; i < columns; i++)
        {
            iss >> coord[i];
        }
        class Point *newPoint = new class Point(name, coord, columns);
        table->push_back(newPoint);
        j++;
    }

    return table;
}