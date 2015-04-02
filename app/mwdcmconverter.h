#ifndef MWDCMCONVERTER_H
#define MWDCMCONVERTER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>

#include "utils.h"

using namespace std;
using boost::optional;
using boost::none;

namespace bf = boost::filesystem;
namespace po = boost::program_options;


class MwDcmConverter
{
public:
    MwDcmConverter(int acc, char *avv[]);

    template<typename T>
    optional<T> get_option(const string & opt_name);

    virtual ~MwDcmConverter();

private:

    void ParseOptions(int acc, char *avv[]);

    po::variables_map vm;

};

#endif // MWDCMCONVERTER_H
