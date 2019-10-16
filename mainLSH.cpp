#include <iostream>
#include <fstream>
#include <ctime>
#include <utility>

#include "point.hpp"
#include "fileReading.hpp"
#include "bruteForce.hpp"
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

    int w = 4500;

    class Reading reader;
    int tableSize;
    vector<class Point *> *inputTable, *queryTable;
    inputTable = reader.readPoints(inputFile);
    queryTable = reader.readPoints(queryFile);

    class LSH lshImplementation(k, L, w, inputTable);
    class Point *q, *b = NULL;
    double distance, tempAF, maxAF = 0.0;
    clock_t timeLSH, timeBrute;

    pair<class Point*, double>* bruteNN;
    ofstream outfile;
    outfile.open(outputFile);


    for (int i = 0; i < queryTable->size(); i++)
    {
        q = (queryTable->at(i));
        timeBrute = clock();
        bruteNN = bruteForce(inputTable, q);
        timeBrute = clock() - timeBrute;
        timeLSH = clock();
        b = lshImplementation.approximateNN(q, &distance);
        timeLSH = clock() - timeLSH;

        tempAF = distance / bruteNN->second;

        if(tempAF > maxAF)
            maxAF = tempAF;

        outfile << "Query Point: " << q->getID() << endl;
        if(b != NULL)
            outfile << "Nearest Neighbor LSH: " << b->getID() << endl << "Distance LSH: " << distance << endl;
        else
            outfile << "Nearest Neighbor LSH: None Found!" << endl << "Distance LSH: -" << endl;
        outfile << "True Neighbor: " << bruteNN->first->getID() << endl << "DistanceTrue: " << bruteNN->second << endl;
        outfile << "tLSH: " << (float) timeLSH/CLOCKS_PER_SEC << endl << "tTrue: " << (float)timeBrute/CLOCKS_PER_SEC << endl << endl;
        delete bruteNN;
        
    }

    cout << maxAF << endl;
    
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
