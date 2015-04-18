#include "mwcsv.h"


mwcsvline::mwcsvline(mwcsvline*  _header, char _delim)
    :header {_header}, delim {_delim}
{

}

mwcsvline::mwcsvline(char _delim): delim {_delim}
{

}


mwcsvline::mwcsvline(const string & a_line, char _delim): delim {_delim}
{
    split_line(a_line,delim);
}

void mwcsvline::split_line(const string & a_line,  char delim)
{
    elems = mw::split(a_line, delim);
}

string mwcsvline::operator[](size_t idx)
{
    return elems.at(idx);
}

ostream& operator<<(ostream& os, const mwcsvline & a_line)
{


    for (size_t i = 0; i< a_line.elems.size()-1;++i)
    {
        os << a_line.elems.at(i) << ",";
    }

    os << a_line.elems.back() << endl;



  return os;
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
        //cout << "FDFD" << str << endl;
        line = mwcsvline(str, ',');
        return true;
   }

   return false;

}

bool
mwcsv::read_header()
{
    return read_line(header);
}


mwcsv::~mwcsv()
{

}

