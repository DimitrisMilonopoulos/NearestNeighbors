#include <iostream>
#include <fstream>
#include <string>

#include "point.hpp"
#include "manhattanDistance.hpp"
#include "bruteForce.hpp"

using namespace std;

pair<class Point*, double>* bruteForce(vector<class Point *> *points, class Point *query)
{    
    size_t npoints = points->size();
    
    pair<class Point*, double>* nearestNeighbor = new pair<class Point*, double>;

    class Point *closestPoint = points->at(0);
    double minDistance = manhattanDist(points->at(0), query);

    class Point* tempPoint;
    double tempDist;
        
    for (int i = 1; i < npoints; i++)
    {
        tempPoint = points->at(i);
        tempDist = manhattanDist(tempPoint, query);
        if (tempDist < minDistance)
        {
            minDistance = tempDist;
            closestPoint = tempPoint;
        }
    }
    nearestNeighbor->first = closestPoint;
    nearestNeighbor->second = minDistance;
    
    return nearestNeighbor;
}

int bruteForceAll(vector<class Point *> *points, vector<class Point *> *queries)
{

    size_t npoints = points->size();
    size_t nqueries = queries->size();

    ofstream outfile;
    outfile.open("brute.dat");
    double avg = 0;

    //for each nqueries find the one with the smallest manhattan distance
    for (int i = 0; i < nqueries; i++)
    {
        double temp_dist, min_distance = manhattanDist(points->at(0), queries->at(i));
        class Point *closest_point = points->at(0);
        for (int j = 1; j < npoints; j++)
        {
            temp_dist = manhattanDist(points->at(j), queries->at(i));
            if (temp_dist < min_distance)
            {
                min_distance = temp_dist;
                closest_point = points->at(j);
            }
        }
        //write the result to the file
        outfile << "Query Point: " << queries->at(i)->getID() << "\tNearest Neighbor: " << closest_point->getID() << "\tDistance: " << min_distance << endl;
        avg += min_distance;
    }
    avg /= nqueries;
    cout << "Average Distance: " << avg << endl;
    outfile.close();
    return 1;
}
