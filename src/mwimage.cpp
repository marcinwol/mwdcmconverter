#include "mwimage.h"


void
MwImage::show()
{
    mimg.display();
}


void
MwImage::read()
{
    mimg.read(img_path.string());
    readProperties();
}

void
MwImage::ping()
{
    mimg.ping(img_path.string());
}

void
MwImage::readProperties()
{
  const char * property;
  const char * value;

  MagickCore::Image * core_image = mimg.image();


  this->properties["format"] = core_image->magick;

  (void) GetImageProperty(core_image,"exif:*");
  (void) GetImageProperty(core_image,"icc:*");
  (void) GetImageProperty(core_image,"iptc:*");
  (void) GetImageProperty(core_image,"xmp:*");

  ResetImagePropertyIterator(core_image);
  property=GetNextImageProperty(core_image);

  if (property != (const char *) NULL)
    {
        while (property != (const char *) NULL)
          {
            value = GetImageProperty(core_image, property);
            this->properties[property] =  value;
            property = GetNextImageProperty(core_image);
          }

    }

  // finally calculate pixel spacfing
  calcResolution();

}


void
MwImage::calcResolution() {

    double ps_x = 0.0;
    double ps_y = 0.0;


    if (!isDCM()) {
        // if not DICOM dont do anything special. Just convert
        // normal density into pixel spacing.

        Magick::Geometry DPI = mimg.density();

        ps_x = DPI.width()  > 0.0 ? 25.4 / DPI.width()   : 0.0;
        ps_y = DPI.height() > 0.0 ? 25.4 / DPI.height()  : 0.0;

        this->resolution = MwResolution(ps_x, ps_y);
        return;

    }

  // to store potential dcm properties for pixelSpacing
  vector<properties_map::value_type> found_properties;

  // first find if we have pixel spacing propertie
  for (const auto & kv: this->properties)
  {
      if (boost::icontains(kv.first, PIXEL_SPACING_KEY_WORD))
      {
          found_properties.push_back(kv);
      }
  }



  if (!found_properties.empty()) {
      // found PixelSpacing propertie,
      // most likly in a dicom file
      string pixel_spacing;

      pixel_spacing = found_properties.at(0).second;
      vector<string> spacing_values = mw::split(pixel_spacing, '\\');

      // trim whitespace
      std::for_each(spacing_values.begin(),
                   spacing_values.end(),
                   [](string & v){boost::trim(v);});

      //my::print_iterable(spacing_values);
      if (!spacing_values.empty()) {


          ps_x = stod(spacing_values.at(0));
          ps_y = stod(spacing_values.at(1));

      }
  } else {
      // no PixelSpacing property. probably not dicom
      // so not surprise. If so, use density information (DPI)
      // and calcate pixel spacing.

      Magick::Geometry DPI = mimg.density();

      ps_x = DPI.width()  > 0.0 ? 25.4 / DPI.width()   : 0.0;
      ps_y = DPI.height() > 0.0 ? 25.4 / DPI.height()  : 0.0;

     // cout << "DPI: "<< DPI.width() << "x" << DPI.height()<< endl;
      //cout << "PS from DPI: "<< ps_x << "x" << ps_y << endl

  }

    this->resolution = MwResolution(ps_x, ps_y);

}


void
MwImage::save_as_tiff(const path & out_path, const string & format)
{

    Magick::Image mimg = get();

    mimg.colorSpace(Magick::GRAYColorspace);
    mimg.compressType(Magick::NoCompression);
    mimg.depth(8);
    mimg.resolutionUnits(Magick::PixelsPerInchResolution);
    mimg.type(Magick::GrayscaleMatteType);

    array<double, 2> dpi = resolution.getDPI();

    Magick::Geometry dip_geometry(72, 72);

    if (dpi[0] > 0 && dpi[1] > 0)
    {
        dip_geometry = Magick::Geometry(int(dpi[0]), int(dpi[1]));
    }

    mimg.density(dip_geometry);

    Magick::Blob b;
    mimg.write(&b, format);

    ofstream oimg(out_path.string(), ifstream::binary);
    oimg.write(static_cast<const char *>(b.data()), b.length());
}



const MwImage::properties_map &
MwImage::getProperties() const
{
  return this->properties;
}

const
MwResolution & MwImage::getResolution() const
{
    return resolution;
}



string
MwImage::getType() const
{
  return string(mimg.magick());
}




bool
MwImage::is_image(const path & img_path_)
{

  try
  {

    Magick::Image img ;

    img.ping(img_path_.string());

    return true;
  }
  catch(Magick::Error & e)
  {
    return false;
  }
  catch(Magick::WarningCorruptImage & e)
  {
    return false;
  }
  catch(Magick::WarningCoder & e)
  {
     return false;
  }
}


MwImage::~MwImage()
{

}

