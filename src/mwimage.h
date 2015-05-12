#ifndef MWIMAGE_H
#define MWIMAGE_H

#include <memory>

#include <Magick++.h>

#include <boost/filesystem.hpp>


#include "mwresolution.h"
#include "utils.h"

using namespace std;
using namespace boost::filesystem;

namespace {
    static const string PIXEL_SPACING_KEY_WORD = "dcm:pixelspacing";
}

class MwImage
{
public:

    using properties_map = std::map<string, string>;

    MwImage(){}

    MwImage(const string & _img_path):img_path(_img_path){}
    MwImage(const path   & _img_path):MwImage(_img_path.string()){}


    void read();
    void ping();

    void readProperties();
    void calcResolution();


    bool isDCM() const {return getType() == "DCM";}

    void show() ;

    Magick::Image & get() {return mimg;}
    string getType() const;
    const properties_map & getProperties() const;
    const MwResolution & getResolution() const;

    void save_as_tiff(const path & out_path, const string & format = "TIFF");



    static bool is_image(const path & img_path_);


    virtual ~MwImage();

private:

    path img_path;
    Magick::Image mimg;
    properties_map properties {};
    MwResolution resolution;

};

#endif // MWIMAGE_H
