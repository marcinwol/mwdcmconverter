#ifndef MWCSV_H
#define MWCSV_H

#include <fstream>

#include <boost/filesystem.hpp>

using namespace boost::filesystem;

using namespace std;

class mwcsv
{
public:
    mwcsv(const string &_fpath);
    mwcsv(const path &_fpath);
    ~mwcsv();
private:
    string   fpath;
    ifstream ifs;
};

#endif // MWCSV_H
