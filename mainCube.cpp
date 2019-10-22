#include <iostream>
#include <fstream>
#include <ctime>
#include <utility>

#include "dataStructs.hpp"
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
    int k = 3, M = 10, probes = 2;

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

    int w = 4500;

    class Reading reader;
    int tableSize;
    vector<class Point *> *inputTable, *queryTable;
    inputTable = reader.readPoints(inputFile);
    queryTable = reader.readPoints(queryFile);

    // bruteForce(inputTable, queryTable);

    class Cube<class Point*> cubeImplementation(k, M, probes, w, inputTable);
    class Point *q, *b = NULL;
    double distance, tempAF, maxAF = 0.0,avgAF=0.0;
    clock_t timeCube, timeBrute;

    pair<class Point*, double>* bruteNN;
    ofstream outfile;
    outfile.open(outputFile);

    for (int i = 0; i < queryTable->size(); i++)
    {
        q = (queryTable->at(i));
        timeBrute = clock();
        bruteNN = bruteForce(inputTable, q);
        timeBrute = clock() - timeBrute;
        timeCube = clock();
        b = cubeImplementation.findNN(q, &distance);
        timeCube = clock() - timeCube;

        tempAF = distance / bruteNN->second;
        avgAF += tempAF;
        if(tempAF > maxAF)
            maxAF = tempAF;

        outfile << "Query Point: " << q->getID() << endl;
        if(b != NULL)
            outfile << "Nearest Neighbor Cube: " << b->getID() << endl << "DistanceCube: " << distance << endl;
        else
            outfile << "Nearest Neighbor Cube: None Found!" << endl << "DistanceCube: -" << endl;
        outfile << "True Neighbor: " << bruteNN->first->getID() << endl << "DistanceTrue: " << bruteNN->second << endl;
        outfile << "tCube: " << (float) timeCube/CLOCKS_PER_SEC << endl << "tTrue: " << (float)timeBrute/CLOCKS_PER_SEC << endl << endl;
        delete bruteNN;
    }

    cout << "MaxAF: " << maxAF << endl;
    cout << "AvgAF: " << avgAF/queryTable->size() <<endl;

    outfile.close();

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