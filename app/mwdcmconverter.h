#ifndef MWDCMCONVERTER_H
#define MWDCMCONVERTER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>


#include "../src/mwimage.h"
#include "../src/mwcsv.h"
#include "../src/utils.h"


#include "../ext/format.h"

using namespace std;
using namespace boost::filesystem;

using boost::optional;
using boost::none;
using boost::lexical_cast;

namespace po = boost::program_options;


class MwDcmConverter
{        
public:

    bool options_ok;

    using paths_vector = vector<mw::fs::found_path_info>;

    static const vector<string> allowed_formats;
    static const map<string, string> new_extentions;


    MwDcmConverter(int acc, char *avv[]);

    void read_in_dir(const path & in_dir,
                     int max_level = -1,
                     bool verbose = true);
    void read_in_csv(const string & in_csv);

    bool create_output_directory(const path & out_dir, bool remove_if_exist);


    template<typename T>
    optional<T> get_option(const string & opt_name) const;

    bool isAllowedFormat(const string & format);

    void test() const;

    const paths_vector & getPaths() const {return found_paths;}

    virtual ~MwDcmConverter();

private:
    void ParseOptions(int acc, char *avv[]);
    paths_vector found_paths;
    po::variables_map vm;
    path input_dir;
    path output_dir;


};



#endif // MWDCMCONVERTER_H
