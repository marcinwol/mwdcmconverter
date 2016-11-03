# mwdcmconverter

`dcmconverter` converts DICOM images into other formats with correct DPI resolution.

# motivation

Working with medical images, especially in DICOM format, 
often requires measuring distances on the images. 
For this, DPI information of the image is vital. 
Unfortunately, most image type conversion programs, 
are not able to convert DICOM images into other formats 
(e.g. TIFF) with correctly set DPI. Also, when working with 
DICOM images from different sources, providing the DPI 
information in the file name can be very useful. 


# Example usage

Convert all dcm images in ~/Desktop/test2/ into tiffs in ~/Desktop/tiffs: 
```
dcmconverter ~/Desktop/test2/ -o ~/Desktop/tiffs --append-dpi --append-distance=12.8
```
 
Convert all dcm images in ~/Desktop/test2/ into tiffs and add dpi info and number of pixels correspoinding to 12.8 mm distance on the images: 
```
dcmconverter ~/Desktop/test2/ --append-dpi --append-distance=12.8
```


