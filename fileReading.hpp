#ifndef _FILE_READING
#define _FILE_READING

#include <vector>
#include <string>
#include "point.hpp"

using namespace std;


class Reading

{
public:
    vector <class Point*> *readPoints(string FileLocation);
};

#endif