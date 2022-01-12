/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <image.h>
#include <misc.h>
#include <pnmfile.h>
#include "segment-image.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include <opencv2/opencv.hpp>

namespace py = pybind11;

void imageTest(py::array_t<uint8_t>& img){
    py::buffer_info buf = img.request();
    cv::Mat mat(buf.shape[0], buf.shape[1], CV_8UC3, (unsigned char*)buf.ptr);
    image<rgb> *im = new image<rgb>(buf.shape[1], buf.shape[0]);
    rgb* imdata = imPtr(im, 0, 0);

    for(int i = 0; i < mat.rows; i++){
        for(int j = 0; j < mat.cols; j++){
            cv::Vec3b bgrPixel = mat.at<cv::Vec3b>(i, j);
            imRef(im, j,i).r = bgrPixel[2];
            imRef(im,j,i).g = bgrPixel[1];
            imRef(im,j,i).b = bgrPixel[0];
        }
    }

    int num_ccs;
    image<rgb> *seg = segment_image(im, 0.5, 500, 20, &num_ccs);
    //savePPM(seg, "out.ppm");

    for(int i = 0; i < mat.rows; i++){
        for(int j = 0; j < mat.cols; j++){
            cv::Vec3b color = cv::Vec3b(
                    imRef(seg,j,i).b,
                    imRef(seg,j,i).g,
                    imRef(seg,j,i).r);
            mat.at<cv::Vec3b>(cv::Point(j,i)) = color;
        }
    }

    //cv::imshow("test", mat);
    //cv::waitKey(0);
}


int main(int argc, char **argv) {
  if (argc != 6) {
    fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);
    return 1;
  }

  float sigma = atof(argv[1]);
  float k = atof(argv[2]);
  int min_size = atoi(argv[3]);

  printf("loading input image.\n");
  image<rgb> *input = loadPPM(argv[4]);

  printf("processing\n");
  int num_ccs;
  image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs);
  savePPM(seg, argv[5]);

  printf("got %d components\n", num_ccs);
  printf("done! uff...thats hard work.\n");

  return 0;
}

PYBIND11_MODULE(segment, m){
    m.doc() = "pybind11 example plugin";
    m.def("imageTest", &imageTest, "A function that adds two numbers");
}
