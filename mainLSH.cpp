#include <iostream>

#include "point.hpp"
#include "fileReading.hpp"
#include "hashTable.hpp"
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

    int w = 1000000;

    cout << inputFile << " " << queryFile << " " << k << " " << L << " " << outputFile << endl;

    class Reading reader;
    int tableSize;
    vector<class Point *> *inputTable, *queryTable;
    inputTable = reader.readPoints(inputFile);
    queryTable = reader.readPoints(queryFile);

    class LSH lshImplementation(k, L, w, inputTable);
    //lshImplementation.approximateNN

    //     Approximate NN
    //         Input : query q
    //                     Let b ←Null; db ← ∞
    // for i from 1 to L do
    // for each item p in bucket gi(q) do
    // if large number of retrieved items (e.g. > 3L) then Break // exit loop
    // end if
    // if dist(q, p) < db then b ← p; db ← dist(q, p)
    // end if
    // end for
    // end for
    // return b

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
