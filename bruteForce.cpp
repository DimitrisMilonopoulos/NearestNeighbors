#include <iostream>
#include <fstream>
#include <string>

#include "bruteForce.hpp"
#include "manhattanDistance.hpp"
#include "point.hpp"

using namespace std;

int bruteForce(vector<class Point*>* points,vector<class Point*>* queries){

    size_t npoints = points->size();
    size_t nqueries = queries->size();

    ofstream outfile;
    outfile.open("brute.dat");
    unsigned int avg=0;

    //for each nqueries find the one with the smallest manhattan distance
    for (int i = 0; i < nqueries; i++)
    {
        unsigned int temp_dist, min_distance = manhattanDist(points->at(0),queries->at(i));
        class Point* closest_point = points->at(0);
        for (int j = 1; j < npoints; j++)
        {
            temp_dist = manhattanDist(points->at(j),queries->at(i));
            if (temp_dist < min_distance){
                min_distance = temp_dist;
                closest_point = points->at(j);
            }
                
        }
        //write the result to the file
        outfile << "Querie :" << queries->at(i)->getID() << "closest to: "<< closest_point->getID() << " dist: " << min_distance <<endl;
        cout <<"Found result for querie " << i+1 <<endl; 
        avg+=min_distance;
    }
    avg /= nqueries;
    cout << "Average Distance "<< avg <<endl;
    outfile.close();
    return 1;
}
