#include "mwcsv.h"



mwcsvline::mwcsvline(char _delim): delim {_delim}
{

}

void mwcsvline::split_line(const string & a_line,  char delim)
{
    elems = mw::split(a_line, delim);
}



mwcsvline::~mwcsvline()
{

}




mwcsv::mwcsv(const string & _fpath):fpath(_fpath), ifs(_fpath)
{

}

mwcsv::mwcsv(const path & _fpath):mwcsv(_fpath.string())
{

}


bool
mwcsv::read_line(mwcsvline & line)
{

   string str;


   if (getline(ifs, str))
   {
        cout << "FDFD" << str << endl;
        line.split_line(str, ',');
        return true;
   }

   return false;



}


mwcsv::~mwcsv()
{

}

