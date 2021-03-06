#include "dcmconverter.h"


const vector<string> MwDcmConverter::allowed_formats  {
       "TIFF", "PNG", "JPEG"};

const map<string, string> MwDcmConverter::new_extentions {
    {"TIFF", ".tiff"},
    {"PNG", ".png"},
    {"JPEG", ".jpg"}
};


MwDcmConverter::MwDcmConverter(int acc, char *avv[])
{
    ParseOptions(acc, avv);
}



void
MwDcmConverter::read_in_dir(const path & in_dir, int max_level, bool verbose)
{
    input_dir = in_dir;
    found_paths =  mw::fs::get_all_paths_fts2(in_dir, max_level, verbose);
}

void
MwDcmConverter::read_in_csv(const string & in_csv)
{


    mwcsv csv {path(in_csv)};

    mwcsvline line {&csv.get_header()};

    while (csv.read_line(line)) {

        string filepath = *line["Filepath"];

        found_paths.push_back(
                    mw::fs::found_path_info {filepath,
                                      atoi((*line["Level"]).c_str()),
                                      path(filepath)}
                    );
    };

}

bool
MwDcmConverter::create_output_directory(const path & out_dir, bool remove_if_exist = false)
{

    try
    {
        if (!is_directory(out_dir))
        {
            if (!mw::fs::create_output_dir(out_dir, remove_if_exist))
            {
                return false;
            }
        }
    }
    catch(const filesystem_error & e)
    {
       mw::errp(e.what());
       return false;
    }

    output_dir = out_dir;

    return true;
}

void
MwDcmConverter::ParseOptions(int acc, char *avv[])
{

    po::positional_options_description p;
    p.add("in-dir", -1);

    po::options_description desc("mwdcmconverter - allowed options"
                                "\n"
                                 "Examples\n"
                                 "mwdcmconverter ~/Desktop/test2/ -o ~/Desktop/tiffs --append-dpi --append-distance=12.8\n"
                                 ""
                                 );

    desc.add_options()
            ("help,h", po::value<bool>()->implicit_value(true),
                      "produce help message")
            ("in-dir,i",  po::value<path>()->default_value(current_path()),
                        "input folder")
            ("out-format,T", po::value<string>()->default_value("TIFF"),
                        "output image format (e.g. TIFF, PNG, JPEG)")
            ("csv-file,c", po::value<string>(),
                            "csv file with files to convert")
            ("out-dir,o", po::value<path>(),
                        "location where the found images will be copied")
            ("overwrite,w", po::value<bool>()->default_value(false),
                         "overwrite output files")
            ("prepend-path", po::bool_switch()->default_value(false),
             "prepend parent folder to the output filename")
            ("append-dpi", po::bool_switch()->default_value(false),
                      "append DPI to the output filename")
            ("append-distance", po::value<double>(),
                      "add numper of pixels that correspond to given "
                      "dinstance [mm]"
                      "based on the DPI")
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

       options_ok = false;
       return;
    }

    if (!isAllowedFormat(vm["out-format"].as<string>()))
    {
        cout << "Given outout format \""
             << vm["out-format"].as<string>()
             << "\" is not supported!\n" << endl;

        cout << desc << "\n";
        options_ok = false;
        return;
    }

    auto csv_file       = get_option<string>("csv-file");

    if (csv_file)
    {
        if (!is_regular_file(*csv_file))
        {
            fmt::print_colored(fmt::RED,
                               "Csv file {} does not exist\n",
                               *csv_file);
            options_ok = false;
            return;
        }
    }

    options_ok = true;

}

template<typename T>
optional<T>
MwDcmConverter::get_option(const string & opt_name) const
{

    if (!vm.count(opt_name))
    {
        return none;
    }

    return vm[opt_name].as<T>();
}

// explicit instantiations of get template function
template optional<string>
MwDcmConverter::get_option<string>(const string & opt_name) const;

template optional<double>
MwDcmConverter::get_option<double>(const string & opt_name) const;

template optional<bool>
MwDcmConverter::get_option<bool>(const string & opt_name) const;

template optional<path>
MwDcmConverter::get_option<path>(const string & opt_name) const;

bool
MwDcmConverter::isAllowedFormat(const string & format)
{
   // return any_of(allowed_formats.begin(), allowed_formats.end(), format);

    if ((find(allowed_formats.begin(), allowed_formats.end(), format)) != allowed_formats.end())
    {
        return true;
    }

    return false;

}

void
MwDcmConverter::test() const
{


    cout << "test reading csv" << endl;

    path csv_file {"/home/m/Desktop/files.csv"};

    mwcsv csv {csv_file};

    mwcsvline line {&csv.get_header()};


    while (csv.read_line(line)) {
        cout << *line["Filepath"] << endl;
    };


}


MwDcmConverter::~MwDcmConverter()
{

}

