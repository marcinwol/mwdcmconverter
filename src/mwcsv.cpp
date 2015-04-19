#include "mwcsv.h"


mwcsvline::mwcsvline(mwcsvline*  _header, char _delim)
    :header {_header}, delim {_delim}
{
   // cout << "const: " << *_header << endl;
}

mwcsvline::mwcsvline(char _delim): delim {_delim}
{

}


mwcsvline::mwcsvline(const string & a_line, char _delim): delim {_delim}
{
    split_line(a_line,delim);
}

void
mwcsvline::split_line(const string & a_line,  char delim)
{
    elems = mw::split(a_line, delim);
}


bool
mwcsvline::find_idx(const string & val, size_t & idx)
{

    vector<string>::iterator it;

    if ((it = find(elems.begin(), elems.end(), val)) != elems.end())
    {
        idx = distance(elems.begin(), it);
        return true;
    }

    return false;
}

string
mwcsvline::operator[](size_t idx)
{
    return elems.at(idx);
}

void
mwcsvline::set_line(const string & in_line)
{
     split_line(in_line, delim);
}

optional<string>
mwcsvline::operator[](const string & col_name)
{

    size_t col_idx;

    if (header->find_idx(col_name, col_idx))
    {

        string col_value = elems[col_idx];

        if (col_value.front() == '"')
        {
            col_value.erase(0, 1);
        }
        if (col_value.back() == '"')
        {
            col_value.erase(col_value.end()-1);
        }

        return make_optional(col_value);
    }



    return none;
}

ostream&
operator<<(ostream& os, const mwcsvline & a_line)
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




mwcsv::mwcsv(const string & _fpath, bool has_header)
    :fpath(_fpath), ifs(_fpath)
{
    if (has_header)
    {
        read_header();
    }
}

mwcsv::mwcsv(const path & _fpath, bool has_header)
    :mwcsv(_fpath.string(), has_header)
{

}


bool
mwcsv::read_line(mwcsvline & line)
{

   string str;


   if (getline(ifs, str))
   {
       // cout << "FDFD" << str << endl;
        line.set_line(str);
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

