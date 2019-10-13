#include <iostream>

#include "point.hpp"
#include "fileReading.hpp"
#include "LSH.hpp"

using namespace std;

// $./lsh –d <input file> –q <query file> –k <int> -L <int> -ο <output file>

int main(int argc, char *argv[])
{
    if (argc > 11)
    {
        cout << "Invalid Input!\n";
        return -1;
    }

    string inputFile, queryFile, outputFile;
    int k = -1, L = -1;

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
        else if (optionBuffer == "-L")
            L = stoi(parameterBuffer, nullptr, 10);
        else if (optionBuffer == "-o")
            outputFile = parameterBuffer;
    }

    if (k == -1)
        k = 3;
    if (L == -1)
        L = 5;

    int w = 5000;

    //cout << inputFile << " " << queryFile << " " << k << " " << L << " " << outputFile << endl;

    class Reading reader;
    int tableSize;
    vector<class Point *> *inputTable, *queryTable;
    inputTable = reader.readPoints(inputFile);
    queryTable = reader.readPoints(queryFile);

    class LSH lshImplementation(k, L, w, inputTable);
    class Point *q, *b;
    unsigned int distance;

    for (int i = 0; i < queryTable->size(); i++)
    {
        q = (queryTable->at(i));
        b = lshImplementation.approximateNN(q, &distance);
        cout << "Query Point: " << q->getID() << "\tNearest Neighbour: " << b->getID() << "\tDistance: " << distance << endl;
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
