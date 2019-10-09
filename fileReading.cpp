#include <iostream>
#include <fstream>
#include <sstream>

#include "fileReading.hpp"

using namespace std;

//Class used to handle the input items

Item::Item(string ID, int *coord, int siz)
{
    itemID = ID;
    coordinates = coord;
    size = siz;
}

Item::~Item()
{
    delete[](coordinates);
}

string Item::getID()
{
    return itemID;
}

int Item::getSize()
{
    return size;
}

//Class used to read the input files

class Item **Reading::readPoints(string FileLocation, int *tableSize)
{
    ifstream infile(FileLocation);
    string line;
    //count the lines of the file
    int count = 0;
    int columns = 0;
    int x;
    ifstream file(FileLocation);
    if (getline(file, line))
    {
        count++;
        //count the columns
        istringstream buffer(line);
        while (buffer >> x)
        {
            columns++;
        }
        columns--; //exclude the item name
    }
    while (getline(file, line))
        count++;

    cout << "Number of lines in file: " << count << '\n';
    cout << "Number of dimensions per point: " << columns << '\n';

    //construct the table of items
    class Item **table = new class Item *[count];
    int j = 0;
    while (getline(infile, line))
    {
        istringstream iss(line);
        //get the name
        string name;
        string buff;
        int *coord = new int[columns];
        iss >> name;
        for (int i = 0; i < columns; i++)
        {
            iss >> coord[i];
        }
        class Item *newitem = new class Item(name, coord, columns);
        table[j] = newitem;
        j++;
    }
    // for (int i = 0; i < count; i++)
    // {
    //     delete (table[i]);
    // }
    // delete[](table);
    *tableSize = count;
    return table;
}