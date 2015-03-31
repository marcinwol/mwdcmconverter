#include "mwdcmconverter.h"

MwDcmConverter::MwDcmConverter(int acc, char *avv[])
{
    cout << "This is dcmconveter" << endl;
    ParseOptions(acc, avv);
}


void
MwDcmConverter::ParseOptions(int acc, char *avv[])
{
    cout << "Parse options" << endl;



    po::positional_options_description p;
    p.add("in-dir", -1);



    po::options_description desc("Allowed options");

    desc.add_options()
            ("help,h", po::value<bool>()->implicit_value(true),
                      "produce help message")
            ("in-dir,i",  po::value<vector<string>>()->multitoken(), "input folder")
            ("out-dir,o", po::value<string>(), "Location where the found images will be copied")
            ("verbose,v", po::bool_switch()->default_value(false),
                            "verbose output")
            ("csv-file,c", po::value<string>(),
                          "output csv file path");


    po::store(po::command_line_parser(acc, avv)
                        .options(desc)
                        .positional(p)
                        .run(), vm);

    po::notify(vm);


}

MwDcmConverter::~MwDcmConverter()
{

}

