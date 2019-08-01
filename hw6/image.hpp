#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

#include <boost/multi_array.hpp>
#include <jpeglib.h>

#include "hw6.hpp"

// void Convolution();
void Convolution(boost::multi_array<unsigned char,2>& input,
                 boost::multi_array<unsigned char,2>& output,
                 boost::multi_array<float,2>&         kernel);

// --------------- image class --------------

class Image{
        boost::multi_array<unsigned char, 2> img;
        boost::multi_array<unsigned char, 2> img_blur;
        boost::multi_array<unsigned char, 2> img_sharp;
        int width;
        int height;
    
    public:
        std::string fname_input;
        int kSize;
        Image(std::string fname_input);
        // void Save(int argc, char *argv[]);
        void Save(std:: string fname_output);
        void BoxBlur(int kSize);
        unsigned int Sharpness();
};

#endif // IMAGE_HPP