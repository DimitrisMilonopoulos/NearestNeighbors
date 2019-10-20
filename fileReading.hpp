#ifndef _FILE_READING
#define _FILE_READING

#include <vector>
#include <string>

using std::string;
using std::vector;

class Reading

{
public:
    vector<class Point *> *readPoints(string FileLocation);
    pair<vector<class Curve *>*,vector<class Curve*>* > readCurves(string FileLocation,int*,int*);
};

#endif