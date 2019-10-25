#include <iostream>
#include <fstream>
#include <ctime>
#include <utility>

#include "dataStructs.hpp"
#include "fileReading.hpp"
#include "bruteForce.hpp"
#include "gridCurve.hpp"
#include "LSH.hpp"
#include "cube.hpp"

using namespace std;

// $./curve –d <input file> –q <query file> –k <int> -L <int> -ο <output file> -a
// {LSH, RandomProjection} –h {LSH, Hypercube} -e <double>

int main(int argc, char *argv[])
{

    ////// Read command line arguments //////
    if (argc > 17)
    {
        cout << "Invalid Input!\n";
        return -1;
    }

    string inputFile, queryFile, outputFile;
    string choice1, choice2;
    int k = 3, L = 5;
    double e = 0.5;

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
        else if (optionBuffer == "-a")
            choice1 = parameterBuffer;
        else if(optionBuffer == "-h")
            choice2 = parameterBuffer;
    }

    ////// Initialize input and queries //////

    int w = 4500;

    class Reading reader;
    int tableSize;
    int minPoints, maxPoints;

    vector<class Curve *> *inputTable, *queryTable;
    pair <vector<class Curve*>*, vector<class Curve*>*> tables;

    double maxCoord = -10000000;

    tables = reader.readCurves(inputFile, &minPoints, &maxPoints,&maxCoord);
    cout << "MAXIMUM COORDINATES " << maxCoord<<endl;
    inputTable = tables.first;
    queryTable = tables.second;

    ofstream outfile;

    outfile.open(outputFile);
    outfile.precision(16);
    double tempAF, maxAF = 0.0, avgAF = 0.0;

    class Curve *q, *b = NULL;
    double distance;
    maxAF = 0.0;
    avgAF = 0.0;
    clock_t timeAlgorithm, timeBrute;

    pair<class Curve*, double>* bruteNN;

    ////// Run algorithm based on the user's choices

    cout << "You chose: " <<choice1<< " "<<choice2 <<endl;

    if(choice1 == "LSH" && choice2 == "LSH")
    {
        class gridCurve<class LSH<class Curve*> >* lshLsh = new class gridCurve<class LSH<class Curve*> >(inputTable, k, L, w, 0, minPoints, maxPoints,maxCoord);
        lshLsh->initializeAlgorithm();
        
        for (int i = 0; i < queryTable->size(); i++)
        {
            q = (queryTable->at(i));
            timeBrute = clock();
            bruteNN = bruteForceCurve(inputTable, q);
            timeBrute = clock() - timeBrute;
            timeAlgorithm = clock();
            b = lshLsh->findNN(q, &distance);
            timeAlgorithm = clock() - timeAlgorithm;

            tempAF = distance / bruteNN->second;
            cout.precision(15);
            cout <<tempAF<<endl;
            avgAF +=tempAF;
            if(tempAF > maxAF)
                maxAF = tempAF;

            outfile << "Query Point: " << q->getID() << endl;
            if(b != NULL)
                outfile << "Nearest Neighbor LSH/LSH: " << b->getID() << endl << "Distance LSH/LSH: " << distance << endl;
            else
                outfile << "Nearest Neighbor LSH/LSH: None Found!" << endl << "Distance LSH/LSH: -" << endl;
            outfile << "True Neighbor: " << bruteNN->first->getID() << endl << "DistanceTrue: " << bruteNN->second << endl;
            outfile << "tLSH/LSH: " << (float) timeAlgorithm/CLOCKS_PER_SEC << endl << "tTrue: " << (float)timeBrute/CLOCKS_PER_SEC << endl << endl;
            delete bruteNN;
        }
        delete lshLsh;
    }
    else if(choice1 == "LSH" && choice2 == "Hypercube")
    {
        class gridCurve<class Cube<class Curve*> >* lshCube = new class gridCurve<class Cube<class Curve*> >(inputTable, k, L, w, 30, minPoints, maxPoints,maxCoord);
        lshCube->initializeAlgorithm();

        for (int i = 0; i < queryTable->size(); i++)
        {
            q = (queryTable->at(i));
            timeBrute = clock();
            bruteNN = bruteForceCurve(inputTable, q);
            timeBrute = clock() - timeBrute;
            timeAlgorithm = clock();
            b = lshCube->findNN(q, &distance);
            timeAlgorithm = clock() - timeAlgorithm;

            tempAF = distance / bruteNN->second;
            avgAF +=tempAF;
            if(tempAF > maxAF)
                maxAF = tempAF;

            outfile << "Query Point: " << q->getID() << endl;
            if(b != NULL)
                outfile << "Nearest Neighbor LSH/Hypercube: " << b->getID() << endl << "Distance LSH/Hypercube: " << distance << endl;
            else
                outfile << "Nearest Neighbor LSH/Hypercube: None Found!" << endl << "Distance LSH/Hypercube: -" << endl;
            outfile << "True Neighbor: " << bruteNN->first->getID() << endl << "DistanceTrue: " << bruteNN->second << endl;
            outfile << "tLSH/Hypercube: " << (float) timeAlgorithm/CLOCKS_PER_SEC << endl << "tTrue: " << (float)timeBrute/CLOCKS_PER_SEC << endl << endl;
            delete bruteNN;
        }
        delete lshCube;
    }
    else if(choice1 == "RandomProjection" && choice2 == "LSH")
    {

    }
    else if(choice1 == "RandomProjection" && choice2 == "Hypercube")
    {

    }

    cout << "MaxAF: "<< maxAF << endl;
    cout <<"AvgAF: " << avgAF/queryTable->size() <<endl;
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
