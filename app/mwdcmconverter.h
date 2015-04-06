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

#include "mwimage.h"
#include "utils.h"


#include "../ext/format.h"

using namespace std;
using namespace boost::filesystem;

using boost::optional;
using boost::none;

namespace po = boost::program_options;


class MwDcmConverter
{        
public:

    using paths_vector = vector<mw::fs::found_path_info>;

    MwDcmConverter(int acc, char *avv[]);

    void read_in_dir(const path & in_dir,
                     int max_level = -1,
                     bool verbose = true);

    bool create_output_directory(const path & out_dir, bool remove_if_exist);


    template<typename T>
    optional<T> get_option(const string & opt_name) const;

    void test() const;

    void process_input_dir();

    virtual ~MwDcmConverter();

private:
    void ParseOptions(int acc, char *avv[]);
    paths_vector found_paths;
    po::variables_map vm;
    path input_dir;
    path output_dir;

};

#endif // MWDCMCONVERTER_H
