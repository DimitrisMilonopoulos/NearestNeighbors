#ifndef _FILE_READING
#define _FILE_READING

#include <vector>
#include <string>

using namespace std;

class Item
{
    string itemID;
    int *coordinates;
    int size;

public:
    Item();
    Item(string ID, int *coord, int siz);
    ~Item();
    string getID();
    int *getCoord();
    int getSize();
};

class Reading
{
public:
    class Item **readInputPoints(string FileLocation, int *tableSize);
    class Item **readQueryPoints(string FileLocation);
};

#endif