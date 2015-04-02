#include "mwdcmconverter.h"

MwDcmConverter::MwDcmConverter(int acc, char *avv[])
{
    ParseOptions(acc, avv);
}


void
MwDcmConverter::ParseOptions(int acc, char *avv[])
{

    po::positional_options_description p;
    p.add("in-dir", -1);

    po::options_description desc("mwdcmconverter - allowed options");

    desc.add_options()
            ("help,h", po::value<bool>()->implicit_value(true),
                      "produce help message")
            ("in-dir,i",  po::value<string>(),
                        "input folder")
            ("out-dir,o", po::value<string>(),
                        "location where the found images will be copied")
            ("csv-file,c", po::value<string>(),
                         "output csv file path")
            ("verbose,v", po::bool_switch()->default_value(false),
                         "verbose output");


    po::store(po::command_line_parser(acc, avv)
                        .options(desc)
                        .positional(p)
                        .run(), vm);

    po::notify(vm);

    if (vm.count("help"))
    {
        cout << desc << "\n";
    }


}

template<typename T>
optional<T>
MwDcmConverter::get_option(const string & opt_name)
{

    if (!vm.count(opt_name))
    {
        return none;
    }

    return vm[opt_name].as<T>();
}

// explicit instantiations of get template function
template optional<string>
MwDcmConverter::get_option<string>(const string & opt_name);

template optional<bool>
MwDcmConverter::get_option<bool>(const string & opt_name);

MwDcmConverter::~MwDcmConverter()
{

}

