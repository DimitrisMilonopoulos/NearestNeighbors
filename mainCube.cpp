#include <iostream>

#include "point.hpp"
#include "fileReading.hpp"
#include "bruteForce.hpp"
#include "hashTable.hpp"
#include "cube.hpp"

using namespace std;

// $./cube –d <input file> –q <query file> –k <int> -M <int> -probes <int> -ο <output file>

int main(int argc, char *argv[])
{

    if (argc < 13)
    {
        cout << "Invalid Input!\n";
        return -1;
    }

    string inputFile, queryFile, outputFile;
    int k = -1, M = -1, probes = -1;

    string optionBuffer, parameterBuffer;

    for (int i = 1; i <= (argc - 1); i += 2)
    {

        optionBuffer = string(argv[i]);
        parameterBuffer = string(argv[i + 1]);

        if (optionBuffer == "-d")
            inputFile = parameterBuffer;
        else if (optionBuffer == "-q")
            queryFile = parameterBuffer;
        else if (optionBuffer == "-k")
            k = stoi(parameterBuffer, nullptr, 10);
        else if (optionBuffer == "-M")
            M = stoi(parameterBuffer, nullptr, 10);
        else if (optionBuffer == "-probes")
            probes = stoi(parameterBuffer, nullptr, 10);
        else if (optionBuffer == "-o")
            outputFile = parameterBuffer;
    }

    if (k == -1)
        k = 3;
    if (M == -1)
        M = 10;
    if (probes == -1)
        probes = 2;

    //cout << inputFile << " " << queryFile << " " << k << " " << M << " " << probes << " " << outputFile << endl;

    int w = 4500;

    class Reading reader;
    int tableSize;
    vector<class Point *> *inputTable, *queryTable;
    inputTable = reader.readPoints(inputFile);
    queryTable = reader.readPoints(queryFile);

    // bruteForce(inputTable, queryTable);

    class Cube cubeImplementation(k, M, probes, w, inputTable);
    class Point *q, *b;
    double distance;

    for (int i = 0; i < queryTable->size(); i++)
    {
        q = (queryTable->at(i));
        b = cubeImplementation.findNN(q, &distance);
        if(q != NULL && b != NULL)
            cout << "Query Point: " << q->getID() << "\tNearest Neighbour: " << b->getID() << "\tDistance: " << distance << endl;
        else
            cout << "No neighbors found!" << endl;
    }

    //delete the tables
    while (!inputTable->empty())
    {
        delete inputTable->back();
        inputTable->pop_back();
    }
    delete (inputTable);

    while (!queryTable->empty())
    {
        delete queryTable->back();
        queryTable->pop_back();
    }
    delete (queryTable);

}