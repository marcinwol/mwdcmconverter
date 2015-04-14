#include "mwcsv.h"

mwcsv::mwcsv(const string & _fpath):fpath(_fpath), ifstream(_fpath)
{

}

mwcsv::mwcsv(const path & _fpath):mwcsv(_fpath.string())
{

}

mwcsv::~mwcsv()
{

}

