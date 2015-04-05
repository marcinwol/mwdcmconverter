#include "mwdcmconverter.h"

MwDcmConverter::MwDcmConverter(int acc, char *avv[])
{
    ParseOptions(acc, avv);
}



void
MwDcmConverter::read_in_dir(const path & in_dir, int max_level, bool verbose)
{
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
            ("overwrite,w", po::value<bool>()->implicit_value(false),
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

    path p {"/mnt/e/ImageDatabases/from_Adolaid/02a_WB_new_discs/DICOMs/D11_1.dcm"};

    MwImage img {p};
    img.read();

    Magick::Image mimg = img.get();

    mimg.colorSpace(Magick::GRAYColorspace);
    mimg.compressType(Magick::NoCompression);
    mimg.depth(8);
    mimg.resolutionUnits(Magick::PixelsPerInchResolution);
    mimg.type(Magick::GrayscaleMatteType);
    mimg.density(Magick::Geometry(36,36));

    cout << mimg.xResolution() << endl;

    mimg.write("/home/marcin/Desktop/test.tiff");

    //Magick::Image mimg2("/home/marcin/Desktop/test2.tiff");

    //mimg2.write(mimg.Image()., "PNG");



}



MwDcmConverter::~MwDcmConverter()
{

}

