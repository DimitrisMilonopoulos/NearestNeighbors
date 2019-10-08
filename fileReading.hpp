#include <vector>
#include <string>

using namespace std;

class Item
{
    string itemID;
    vector<int> *coordinates;

public:
    Item(string ID);
    ~Item();
    string getID();
    vector<int> *getCoord();
    void Item::addCoord(int coord);
};

class Reading
{
public:
    vector<class Item> *readInputPoints(string FileLocation);
    vector<class Item> *readQueryPoints(string FileLocation);
};