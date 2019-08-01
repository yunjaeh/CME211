#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

#define BOOST_DISABLE_ASSERTS
#include <boost/multi_array.hpp>
#include <jpeglib.h>

#include "hw6.hpp"
#include "image.hpp"


// convolution function
void Convolution(boost::multi_array<unsigned char,2>& input,
                 boost::multi_array<unsigned char,2>& output,
                 boost::multi_array<float,2>&         kernel)
{
    int width = (int) input[0].size();
    int height = (int) input.size();
    int kSize = (int) kernel.size();

    if( (kSize%2) ==0){
        throw std::invalid_argument("kernel size is not odd");
        std::exit(0);
    }
    int range = (kSize-1)/2;
    
    // std::cout << kSize << ", "<<range << std::endl;
    float value = 0.0;
    for(int i=0+range;i<height-range;i++)
    {
        for(int j=0+range;j<width-range;j++)
        {
            value = 0.0;
            for(int ii=-1*range;ii<=range;ii++)
            {
                for(int jj=-1*range;jj<=range;jj++)
                {
                    value +=  (float) input[i+ii][j+jj]*kernel[range+ii][range+jj];
                }
            }
            output[i][j]=(unsigned char) abs( (int) value);
        }
    }
}




// class "Image"
Image::Image(std::string fname_input)
{
    this -> fname_input = fname_input;
    ReadGrayscaleJPEG(fname_input, img);
    width = (int) img[0].size();
    height = (int) img.size();
}


// method "Save"
void Image::Save(std::string fname_output)
{
    WriteGrayscaleJPEG(fname_output, img_blur);
}


// method "BoxBlur"
void Image::BoxBlur(int kSize)
{
    this -> kSize = kSize;

    img_blur.resize(boost::extents[height][width]);   
    boost::multi_array<float,2> kernel(boost::extents[kSize][kSize]);

    for(int i=0;i<kSize;i++)
    {
        for(int j=0;j<kSize;j++)
        {
            kernel[i][j] = (float) (1.0 / (kSize*kSize));
        }
    }

    Convolution(img, img_blur, kernel);
        
    // process edge, extrapolation
    int range = (kSize-1)/2;

    for(int i=range;i<(height-range);i++) 
    {
        for(int j=0;j<range;j++) 
        {
            img_blur[i][j]=img_blur[i][range];
        }
        for(int j=(width-range);j<width;j++) 
        {
            img_blur[i][j]=img_blur[i][width-range-1];
        }
    }

    for(int j=0;j<width;j++) 
    {
        for(int i=0;i<range;i++) 
        {
            img_blur[i][j]=img_blur[range][j];
        }
        
        for(int i=(height-range);i<height;i++) 
        {
            img_blur[i][j]=img_blur[height-range-1][j];
        }
                
    }
}

// method "Sharpness"
unsigned int Image::Sharpness()
{
    img_sharp.resize(boost::extents[height][width]);
    boost::multi_array<float,2> Laplacian(boost::extents[3][3]);
    Laplacian[0][1] = 1.0;
    Laplacian[1][0] = 1.0;
    Laplacian[1][1] = -4.0;
    Laplacian[1][2] = 1.0;
    Laplacian[2][1] = 1.0;

    Convolution(img_blur,img_sharp,Laplacian);

    unsigned int MAX = 0;
    for(int i=2;i<height-2;i++)
    {
        for(int j=2;j<width-2;j++)
        {
            if( img_sharp[i][j]> MAX)
            {
                MAX = (unsigned int) img_sharp[i][j];
            } 
        }
    }
    return MAX;
}