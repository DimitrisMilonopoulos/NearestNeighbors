#include <iostream>
#include <string>

#include "point.hpp"
#include "fileReading.hpp"
#include "manhattanDistance.hpp"
#include "dynamicTimeWarping.hpp"

using namespace std;

double DTWDistance(class Curve *P, class Curve *Q){

    int length = P->getSize();
    int width = Q->getSize();

    double **C = new double*[length];

    for (int i = 0; i < length; i ++)
    {
        C[i] = new double[width]; 
    }

    double minimum, result = 0.0;

    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if( i == 0 && j == 0){
                C[i][j] = manhattanDist(P->getCoord()[i], Q->getCoord()[j]);
            }
            else if(j > 0 && i == 0)
            {
                C[i][j] = C[i][j-1] + manhattanDist(P->getCoord()[i], Q->getCoord()[j]);
            }
            else if(i > 0 && j == 0)
            {
                C[i][j] = C[i-1][j] + manhattanDist(P->getCoord()[i], Q->getCoord()[j]);

            }
            else
            {
                minimum = min(min(C[i-1][j], C[i-1][j-1]), C[i][j-1]);
                C[i][j] = minimum + manhattanDist(P->getCoord()[i], Q->getCoord()[j]);
                minimum = 0.0;
            }
        }
    }

    result = C[length-1][width-1];
    
    for(int i = 0; i < length; i++){
        delete [] C[i];
    }

    delete [] C;
    
    return result;
}

// int main(){

//     class Reading reader;
//     int tableSize;
//     vector<class Point *> *inputTable;
//     inputTable = reader.readPoints("./input");

//     int index = 0;
//     vector<class Point*>* P = new vector<class Point*>[3];
//     vector<class Point*>* Q = new vector<class Point*>[2];

//     while(index < 5){
//         cout << index<< endl;
//         if(index < 3)
//             P->push_back(inputTable->at(index));
//         else
//             Q->push_back(inputTable->at(index));
//         index++;
//     }

//     double result = DTWDistance(P, Q);
//     cout << result << endl;

//     delete [] P;
//     delete [] Q;

//     while (!inputTable->empty())
//     {
//         delete inputTable->back();
//         inputTable->pop_back();
//     }
//     delete (inputTable);

//     return 0;
// }