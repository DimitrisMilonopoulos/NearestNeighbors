#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

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
        class Point *newPoint = new class Point(name, coord, columns,NULL);
        table->push_back(newPoint);
        j++;
    }

    return table;
}

template <char C>
std::istream& expect(std::istream& in)
{
    if ((in >> std::ws).peek() == C) {
        in.ignore();
    }
    else {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

vector <class Curve*> *Reading::readCurves(string FileLocation){
    ifstream infile(FileLocation);
    string line;
    vector <class Curve*> *inputTable = new vector <class Curve*>;
    while(getline(infile,line)){
        istringstream iss(line);
        int points;
        string ID,buff;
        iss >> ID;
        iss >> points;
        pair <double, double> * coord = new pair<double, double>[points];
        pair <double, double> mypair;
        for (size_t i = 0; i < points; i++)
        {
            //read first part of the string
            iss>>buff;
            sscanf(buff.c_str(),"(%lf,",&coord[i].first);
            iss>>buff;
            sscanf(buff.c_str(),"%lf)",&coord[i].second);
        }
        class Curve *curve = new class Curve(ID,coord,points);
        inputTable->push_back(curve);
    }
    

    return inputTable;
}