#ifndef _FILE_READING
#define _FILE_READING

#include <vector>
#include <string>

using namespace std;

class Point
{
    string PointID;
    int *coordinates;
    int size;

public:
    Point();
    Point(string ID, int *coord, int siz);
    ~Point();
    string getID();
    int *getCoord();
    int getSize();
};

class Reading
{
public:
    class Point **readPoints(string FileLocation, int *tableSize);
};

#endif