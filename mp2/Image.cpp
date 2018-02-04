#include "Image.h"

using namespace cs225;

void Image::lighten()
{
  for(unsigned int i=0; i<height(); i++)
  {
    for(unsigned int j=0; j<width();j++)
    {
      HSLAPixel &image = getPixel(j, i);
      if(image.l+.1 <= 1.0)
        image.l = image.l +.1;
      else
          image.l = 1.0;
    }
  }
}

void Image::lighten(double amount)
{
  for(unsigned int i=0; i<height(); i++)
  {
    for(unsigned int j=0; j<width();j++)
    {
      HSLAPixel &image = getPixel(j, i);
      if(image.l+amount <= 1.0)
        image.l = image.l + amount;
      else
        image.l = 1.0;
    }
  }
}

void Image::darken()
{
  for(unsigned int i=0; i<height(); i++)
  {
    for(unsigned int j=0; j<width();j++)
    {
      HSLAPixel &image = getPixel(j, i);
      if(image.l-.1 >= 0)
        image.l = image.l -.1;
      else
        image.l = 0.0;
    }
  }
}

void Image::darken (double amount)
{
  for(unsigned int i=0; i<height(); i++)
  {
    for(unsigned int j=0; j<width();j++)
    {
      HSLAPixel &image = getPixel(j, i);
      if(image.l-amount >= 0.0)
        image.l = image.l - amount;
      else
          image.l = 0.0;
    }
  }
}

void Image::saturate()
{
  for(unsigned int i=0; i<height(); i++)
  {
    for(unsigned int j=0; j<width();j++)
    {
      HSLAPixel &image = getPixel(j, i);
      if(image.s+.1 <= 1.0)
        image.s = image.s +.1;
      else
        image.s = 1.0;
    }
  }
}

void Image::saturate(double amount)
{
  for(unsigned int i=0; i<height(); i++)
  {
    for(unsigned int j=0; j<width();j++)
    {
      HSLAPixel &image = getPixel(j, i);
      if(image.s+amount <= 1.0)
        image.s = image.s + amount;
      else
          image.s = 1.0;
    }
  }
}

void Image::desaturate()
{
  for(unsigned int i=0; i<height(); i++)
  {
    for(unsigned int j=0; j<width();j++)
    {
      HSLAPixel &image = getPixel(j, i);
      if(image.s-.1 >= 0.0)
        image.s = image.s -.1;
      else
        image.s = 0.0;
    }
  }
}

void Image::desaturate(double amount)
{
  for(unsigned int i=0; i<height(); i++)
  {
    for(unsigned int j=0; j<width();j++)
    {
      HSLAPixel &image = getPixel(j, i);
      if(image.s-amount >= 0.0)
        image.s = image.s - amount;
      else
        image.s = 0.0;
    }
  }
}

void Image::grayscale()
{
  for(unsigned int i=0; i<height(); i++)
  {
    for(unsigned int j=0; j<width();j++)
    {
      HSLAPixel &image = getPixel(j, i);
      image.s = 0;
    }
  }
}

void Image::rotateColor(double degrees)
{
  for(unsigned int i=0; i<height(); i++)
  {
    for(unsigned int j=0; j<width();j++)
    {
      HSLAPixel &image = getPixel(j, i);
      image.h = image.h + degrees;
      //Degrees chosen could be ridiculously large
      while(image.h > 360)
      {
        image.h = image.h - 360;
      }
      while(image.h < 0)
        image.h = image.h +360;
    }
  }
}

void Image::illinfy()
{
  for(unsigned int i=0; i<height(); i++)
  {
    for(unsigned int j=0; j<width();j++)
    {
      HSLAPixel &pixel = getPixel(j, i);
      if(pixel.h<=329 && pixel.h>=103)          //Illini blue between these values
       {
        pixel.h = 216;
       }
    else
    /*11 was chosen for else statement because then you don't have to worry about
    the 0/360 value of the color circle*/
       {
        pixel.h = 11;                           //Illini orange
       }

    }
  }
}

void Image::scale(double factor)
{
  // Create a new vector to store the image data for the new (resized) image
    unsigned int newWidth = width() * factor;
    unsigned int newHeight = height() * factor;
    HSLAPixel *newImageData = new HSLAPixel[newWidth * newHeight];

      // Copy the current data to the new image data, using the existing pixel
      // for coordinates within the bounds of the old image size
      for (unsigned x = 0; x < newWidth; x++) {
        for (unsigned y = 0; y < newHeight; y++) {
          if (x < width() && y < height()) {
            HSLAPixel & oldPixel = this->getPixel(x, y);
            HSLAPixel & newPixel = newImageData[ (x + (y * newWidth)) ];
            newPixel = oldPixel;
          }
        }
      }

      // Clear the existing image
      delete[] newImageData;
}

void Image::scale(unsigned w, unsigned h)
{
  // Create a new vector to store the image data for the new (resized) image
    unsigned int newWidth = w;
    unsigned int newHeight = h;
    HSLAPixel *newImageData = new HSLAPixel[newWidth * newHeight];

      // Copy the current data to the new image data, using the existing pixel
      // for coordinates within the bounds of the old image size
      for (unsigned x = 0; x < newWidth; x++) {
        for (unsigned y = 0; y < newHeight; y++) {
          if (x < width() && y < height()) {
            HSLAPixel & oldPixel = this->getPixel(x, y);
            HSLAPixel & newPixel = newImageData[ (x + (y * newWidth)) ];
            newPixel = oldPixel;
          }
        }
      }

      // Clear the existing image
      delete[] newImageData;
}
