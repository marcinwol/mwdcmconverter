#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


#include "mwdcmconverter.h"




int main(int ac, char* av[])
{


    MwDcmConverter app {ac, av};

    // get program options
    auto verbose   = app.get_option<bool>("verbose");
    auto in_dir    = app.get_option<string>("in-dir");
    auto out_dir   = app.get_option<string>("out-dir");
    auto csv_file  = app.get_option<string>("csv-file");

    if (in_dir)
    {
        cout << *in_dir << endl;
    }

    return 0;
}
