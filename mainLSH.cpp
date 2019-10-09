#include <iostream>
#include "fileReading.hpp"

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
    int k, L;

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

    cout << inputFile << " " << queryFile << " " << k << " " << L << " " << outputFile << endl;

    class Reading reader;
    int tableSize;
    vector <class Point*>* inputTable;
    inputTable = reader.readPoints(inputFile);

    //delete the table
    delete[](inputTable);
}