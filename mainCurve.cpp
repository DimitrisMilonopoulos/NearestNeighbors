#include <iostream>
#include <fstream>
#include <ctime>
#include <utility>

#include "point.hpp"
#include "fileReading.hpp"
#include "bruteForce.hpp"
#include "LSH.hpp"

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

    tables = reader.readCurves(inputFile, &minPoints, &maxPoints);
    inputTable = tables.first;
    queryTable = tables.second;

    ofstream outfile;
    outfile.open(outputFile);

    double tempAF, maxAF = 0.0, avgAF = 0.0;

    ////// Run algorithm based on the user's choices

    if(choice1 == "LSH" && choice2 == "LSH")
    {
        cout << k << endl;
        class LSH<class Curve*> lshImplementation(k, L, w, inputTable, minPoints, maxPoints);
        class Curve *q, *b = NULL;
        double distance;
        maxAF = 0.0;
        avgAF = 0.0;
        clock_t timeLSH, timeBrute;

        pair<class Curve*, double>* bruteNN;

        for (int i = 0; i < queryTable->size(); i++)
        {
            q = (queryTable->at(i));
            timeBrute = clock();
            bruteNN = bruteForceCurve(inputTable, q);
            timeBrute = clock() - timeBrute;
            timeLSH = clock();
            b = lshImplementation.approximateNN(q, &distance);
            timeLSH = clock() - timeLSH;

            tempAF = distance / bruteNN->second;
            avgAF +=tempAF;
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
    }
    else if(choice1 == "LSH" && choice2 == "Hypercube")
    {

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
