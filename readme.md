# Felzenszwalb
A fast C++ implementation of the felzenszwalb segmentation algorithm adapted from [http://cs.brown.edu/people/pfelzens/segment/](http://cs.brown.edu/people/pfelzens/segment/).

## Installation Notes
todo

make sure that you have the correct version python3.x-dev installed on your machine (if you are on ubunut)

## Notes
### PPM image format
the original implementation uses this ridiculous image format called PPM. This appears to be an uncompressed image binary representation. The internal class representation of an Image is also simple enough and can be found in include/image.h. The underlying data is just a byte array which consists of red, green, blue values. More about this can be found at this resource: [http://netpbm.sourceforge.net/doc/ppm.html](http://netpbm.sourceforge.net/doc/ppm.html)

## Todo
 - [ ] Speed up the transformation between image representations
 - [ ] parallelize using openmp
 - [ ] get the inference speed down to 1/2 second
