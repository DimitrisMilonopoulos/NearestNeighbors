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
    vector<class Curve *> *readCurves(string FileLocation);
};

#endif