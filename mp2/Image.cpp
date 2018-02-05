#include "Image.h"

using namespace cs225;

void Image::lighten()
{
  for(unsigned int i=0; i<height(); i++)      //Loops through every row
  {
    for(unsigned int j=0; j<width();j++)      //Loops through every column
    {
      HSLAPixel &image = getPixel(j, i);      //Creates a reference variable
      if(image.l+.1 <= 1.0)                   //Changes luminance by .1
        image.l = image.l +.1;
      else                                    //Or sets to 1.0
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
      if(image.l+amount <= 1.0)               //Changes luminace by an amount
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
      if(image.l-.1 >= 0)                   //Decreases luminace by .1
        image.l = image.l -.1;
      else                                  //Or sets to 0
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
      if(image.l-amount >= 0.0)             //Decreases luminance by amount
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
      if(image.s+.1 <= 1.0)               //Changes saturation by .1
        image.s = image.s +.1;
      else                                //Changes saturation to 1
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
      if(image.s+amount <= 1.0)           //Changes saturation by an amount
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
      if(image.s-.1 >= 0.0)              //Changes saturation by -.1
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
      if(image.s-amount >= 0.0)           //Decreases saturation by an amount
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
      //Degrees chosen could be ridiculously large, so have to adjust
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
    PNG *middleman = new PNG(newWidth, newHeight);

    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & oldPixel = getPixel(x, y);

          for(unsigned i=x*factor; i <(x*(factor)+factor); i++){
            for(unsigned j=y*factor; j < (y*(factor)+factor); j++){
              HSLAPixel & newPixel = middleman->getPixel(i, j);
              newPixel = oldPixel;
            }
          }
      }
    }

    resize(newWidth, newHeight);

    for (unsigned x = 0; x < newWidth; x++) {
      for (unsigned y = 0; y < newHeight; y++) {
          HSLAPixel & oldPixel = getPixel(x, y);
          HSLAPixel & newPixel = middleman->getPixel(x, y);
          oldPixel = newPixel;
        }
      }
    delete middleman;
}

void Image::scale(unsigned w, unsigned h)
{
  unsigned int newWidth = h;
  unsigned int newHeight = h;
  double factor = h / width();

  if(w > h)
  {
    newWidth = w;
    newHeight = w;
    factor = w / width();

  }
  PNG *middleman = new PNG(newWidth, newHeight);

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & oldPixel = getPixel(x, y);

        for(unsigned i=x*factor; i <(x*(factor)+factor); i++){
          for(unsigned j=y*factor; j < (y*(factor)+factor); j++){
            HSLAPixel & newPixel = middleman->getPixel(i, j);
            newPixel = oldPixel;
          }
        }
    }
  }

  resize(newWidth, newHeight);

  for (unsigned x = 0; x < newWidth; x++) {
    for (unsigned y = 0; y < newHeight; y++) {
        HSLAPixel & oldPixel = getPixel(x, y);
        HSLAPixel & newPixel = middleman->getPixel(x, y);
        oldPixel = newPixel;
      }
    }
  delete middleman;
}
