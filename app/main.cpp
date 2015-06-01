#define BOOST_NO_CXX11_SCOPED_ENUMS


#include "mwdcmconverter.h"



int main(int ac, char* av[])
{


    MwDcmConverter app {ac, av};

    // get program options
    auto verbose        = app.get_option<bool>("verbose");
    auto in_dir         = app.get_option<path>("in-dir");
    auto out_dir        = app.get_option<path>("out-dir");
    auto overwrite      = app.get_option<bool>("overwrite");
    auto csv_file       = app.get_option<string>("csv-file");
    auto output_format  = app.get_option<string>("out-format");
    auto append_dpi     = app.get_option<bool>("append-dpi");
    auto distance       = app.get_option<double>("append-distance");


    if (!app.options_ok)
    {
        return 1;
    }

    // if csv_file not provided use in_dir
    // otherwise use the files fromt he csv_file
    if (in_dir && !csv_file)
    {
        app.read_in_dir(*in_dir);
    }
    else
    {
        app.read_in_csv(*csv_file);
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


    // get found paths of files in the input directory
    const MwDcmConverter::paths_vector found_files = app.getPaths();
    size_t files_no = found_files.size();
    size_t indx {0};


    // process each path and convert images to grayscale, 8-bit tiffs
    for (const mw::fs::found_path_info & a_path: found_files)
    {
        cout << a_path.fpath << endl;

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

        string out_filename = fileparts["basename"];

        if (*verbose)
        {
            fmt::print("Reading {}/{}: {} ...\n",
                        indx, files_no, in_file_path.string());
        }
        else
        {
            cout  << "\r" << fmt::format("Processing file {}/{} ...",
                                         indx, files_no)
                          << flush;
        }

        MwImage img {in_file_path};
        img.read();


        if (*append_dpi)
        {
            array<double, 2> dpi = img.getResolution().getDPI();
            out_filename += fmt::format("_DPI{:03d}",
                                        static_cast<int>(dpi[0]+0.5));
        }

        if (distance)
        {
            array<double, 2> dpi = img.getResolution().getDPI();
            double pixel_length = (*distance) / (25.4/dpi[0]);
            out_filename += fmt::format("_d{:03d}px",
                                        static_cast<int>(pixel_length+0.5));
        }


        out_filename +=  app.new_extentions.at(*output_format);

        path out_path = *out_dir / path(out_filename);




        if (*verbose)
        {
            fmt::print("\t -saving converted to: {}\n", out_path.string());
        }

        img.save_as_tiff(out_path, *output_format);
    }

    cout << endl;


    return 0;
}
