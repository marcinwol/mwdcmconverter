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
    mwcsvline(mwcsvline* _header, char _delim = ',');

    mwcsvline(char _delim = ',');
    mwcsvline(const string & a_line, char _delim = ',');        

    void split_line(const string & a_line, char delim);
    virtual ~mwcsvline();
    string operator[](size_t idx);

private:    
    mwcsvline* header;
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

    bool read_header();
    bool read_line(mwcsvline & line);
    mwcsvline & get_header() {return header;}

    virtual ~mwcsv();
private:    
    string   fpath;
    ifstream ifs;    
    mwcsvline header;
};

#endif // MWCSV_H
