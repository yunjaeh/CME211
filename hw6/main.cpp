#include <sstream>
#include <stdexcept>
#include <string>

#define BOOST_DISABLE_ASSERTS
#include <boost/multi_array.hpp>
#include <jpeglib.h>
#include <stdio.h>

#include "hw6.hpp"
#include "image.hpp"


int main(void) 
{
    char s1[20];
    char s2[20];
    std::string fname;
    
    Image a("stanford.jpg");

    a.BoxBlur(1);
    std::cout <<  "Original image:  " << a.Sharpness() << std::endl;
    for(int i=3;i<28;i+=4)
    {
        a.BoxBlur(i);
        sprintf(s1,"BoxBlur%02d.jpg",i);
        a.Save(s1);
        sprintf(s2,"BoxBlur(%2d):%8d", i, a.Sharpness());
        std::cout << s2 << std::endl;
    }
   

  return 0;
}
