#include "mwdcmconverter.h"


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

bool MwDcmConverter::create_output_directory(const path & out_dir, bool remove_if_exist = false)
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

    po::options_description desc("mwdcmconverter - allowed options");

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
            ("csv-file,c", po::value<string>(),
                         "output csv file path")
            ("overwrite,w", po::value<bool>()->default_value(false),
                         "overwrite output files")
            ("append-dpi", po::bool_switch()->default_value(false),
                      "append DPI to the output filename")
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
    }

    if (!isAllowedFormat(vm["out-format"].as<string>()))
    {
        cout << "Given outout format \""
             << vm["out-format"].as<string>()
             << "\" is not supported!\n" << endl;

        cout << desc << "\n";
        options_ok = false;
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

    cout << "test" << endl;

   // path p {"/media/sf_D_DRIVE/dcm_for_tests/moa/159169_1_anon/im_3/i0000,0000b-no-phi.dcm"};

    path p {"/media/sf_D_DRIVE/dcm_for_tests/most/MB00019_KFLK/V0/20030418/20018/PA10/200181.dcm"};

    MwImage img {p};
    img.read();


    img.save_as_tiff("/home/m/Desktop/test2", "TIFF");




    //mimg.write("/home/m/Desktop/test2");

//    Magick::Blob b;
//    mimg.write(&b, "TIFF");



//   // cout.write(static_cast<const char *>(b.data()), b.length());

//    ofstream oimg("/home/m/Desktop/test2.jpg", ifstream::binary);
//    oimg.write(static_cast<const char *>(b.data()), b.length());




}


MwDcmConverter::~MwDcmConverter()
{

}

