#define BOOST_NO_CXX11_SCOPED_ENUMS


#include "mwdcmconverter.h"



int main(int ac, char* av[])
{


    MwDcmConverter app {ac, av};

    // get program options
    auto verbose   = app.get_option<bool>("verbose");
    auto in_dir    = app.get_option<path>("in-dir");
    auto out_dir   = app.get_option<path>("out-dir");
    auto overwrite = app.get_option<bool>("overwrite");
    auto csv_file  = app.get_option<string>("csv-file");

    if (in_dir)
    {
        app.read_in_dir(*in_dir);
    }

    if (!out_dir)
    {
        // if out_dir not given, use in_dir as out_dir
        out_dir = in_dir;
    }
    else
    {                                        
        // if out_dir given, than create it if needed
        if (!app.create_output_directory(*out_dir, *overwrite))
        {
            fmt::print_colored(fmt::RED, "Cant create {}\n", *out_dir);
            return 1;
        }
    }


    const MwDcmConverter::paths_vector found_files = app.getPaths();
    size_t files_no = found_files.size();
    size_t indx {0};



    for (const mw::fs::found_path_info & a_path: found_files)
    {
        //cout << a_path.fpath << endl;

        path in_file_path = a_path.fpath;

        indx++;

        if (!MwImage::is_image(in_file_path))
        {

            if (*verbose)
            {
                fmt::print("Not an image: {}\n", in_file_path.string());
            }

            continue;
        }

        map<string, string> fileparts = mw::fs::getfileparts(in_file_path);

        path out_path = *out_dir / path(fileparts["basename"]+".tiff");

        if (*verbose)
        {
            fmt::print("Reading {} ...\n", in_file_path.string());
        }
        else
        {
            cout  << "\r" << fmt::format("Processing file {}/{} ...", indx, files_no)
                          << flush;
        }


        MwImage img {in_file_path};
        img.read();

        if (*verbose)
        {
            fmt::print("\t -saving converted to: {}\n", out_path.string());
        }
        img.save_as_tiff(out_path, "TIFF");
    }


    return 0;
}
