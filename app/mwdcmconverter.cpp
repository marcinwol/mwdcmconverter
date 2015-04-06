#include "mwdcmconverter.h"

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
            ("out-dir,o", po::value<path>(),
                        "location where the found images will be copied")
            ("csv-file,c", po::value<string>(),
                         "output csv file path")
            ("overwrite,w", po::value<bool>()->default_value(false),
                         "overwrite output files")
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

void
MwDcmConverter::process_input_dir()
{

    for (const mw::fs::found_path_info & a_path: found_paths)
    {
        //cout << a_path.fpath << endl;

        path in_file_path = a_path.fpath;

        if (!MwImage::is_image(in_file_path))
        {
            continue;
        }

        map<string, string> fileparts = mw::fs::getfileparts(in_file_path);

        path out_path = output_dir / path(fileparts["basename"]+".tiff");


        MwImage img {in_file_path};
        img.read();

        fmt::print("Saving to: {}\n", out_path.string());

        img.save_as_tiff(out_path, "TIFF");

    }

}




MwDcmConverter::~MwDcmConverter()
{

}

