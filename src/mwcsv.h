#ifndef MWCSV_H
#define MWCSV_H

#include <vector>
#include <fstream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/optional.hpp>

#include "utils.h"

using namespace boost::filesystem;

using namespace std;

using boost::optional;
using boost::none;
using boost::make_optional;

class mwcsvline
{
public:

   mwcsvline* header;


    mwcsvline(mwcsvline* _header, char _delim = ',');

    mwcsvline(char _delim = ',');
    mwcsvline(const string & a_line, char _delim = ',');

    void split_line(const string & a_line, char delim);
    virtual ~mwcsvline();

    void set_line(const string & in_line);

    bool find_idx(const string & val, size_t & idx);

    string operator[](size_t idx);
    optional<string> operator[](const string & col_name);

private:    

    char delim;
    vector<string> elems;


    // friends
    friend ostream & operator<<(ostream & os, const mwcsvline & a_line);

};


class mwcsv
{
public:
    mwcsv(const string &_fpath, bool has_header = true);
    mwcsv(const path &_fpath, bool has_header = true);

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
