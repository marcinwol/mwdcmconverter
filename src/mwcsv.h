#ifndef MWCSV_H
#define MWCSV_H

#include <vector>
#include <fstream>
#include <string>

#include <boost/filesystem.hpp>

#include "utils.h"

using namespace boost::filesystem;

using namespace std;

class mwcsvline
{
public:
    mwcsvline(char _delim = ',');
    mwcsvline(const string & a_line, char _delim = ',');
    void split_line(const string & a_line, char delim);
    virtual ~mwcsvline();

private:    
    char delim;
    vector<string> elems;

    // friends
    friend ostream & operator<<(ostream & os, const mwcsvline & a_line);

};


class mwcsv
{
public:
    mwcsv(const string &_fpath);
    mwcsv(const path &_fpath);

    bool read_line(mwcsvline & line);

    virtual ~mwcsv();
private:    

    string   fpath;
    ifstream ifs;
};

#endif // MWCSV_H
