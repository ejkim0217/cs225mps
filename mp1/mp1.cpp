#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <iostream>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
  PNG *input = new PNG;
  input->readFromFile(inputFile);
  unsigned int height = input->height();
  unsigned int width = input->width();

  PNG *output = new PNG(width, height);

  for(unsigned int i=0; i<width; i++)
  {
    for(unsigned int j=0; j<height;j++)
    {
      HSLAPixel *currIn = input->getPixel(i, j);
      HSLAPixel *currOut = output->getPixel((width-1-i),(height-1-j));
      *currOut = *currIn;
    }
  }
  output->writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3
  unsigned int mid_w = width/2;

  for(unsigned int i=0; i<mid_w; i++)
  {
    for(unsigned int j=0; j<height; j++)
    {
      HSLAPixel *pixel = png.getPixel(i,j);
      pixel->h = 310 * (400-i)/400;
      /*This formula is meant to simulate the Doppler Effect. 400 can be considered
      the speed of light in this artifical medium and i could be the velocity of
      the source relative to the observer as it moves. I inverted the formula with
      1/((v/v-vs)*f) so that the values obtained matched up with the [0, 360] degree
      wheel I was limited with.
      */
      pixel->s = 1.0;
      pixel->l = .5;
      pixel->a = 1.0;
    }
  }
  for(unsigned int i=mid_w; i<width; i++)
  {
    for(unsigned int j=0; j<height; j++)
    {
      HSLAPixel *pixel = png.getPixel(i,j);
      pixel->h = -1*310*(400-i)/400;    //Same as above
      pixel->s = 1.0;
      pixel->l = .5;
      pixel->a = 1.0;
    }
  }
  /*
  for(unsigned int i=0; i<width; i++)
  {
    for(unsigned int j=0; j<height; j++)
    {
      HSLAPixel *pixel = png.getPixel(i,j);
      pixel->h = 216;
      pixel->s = 1.0;
      pixel->l = .5;
      pixel->a = 1.0;
    }
  }

  for(unsigned int j = height/8; j<(height*3/8);j++)
  {
    for(unsigned int i=(width/8);i<(width*7/8);i++)
    {
      HSLAPixel *pixel = png.getPixel(i,j);
      pixel->h = 22;
      pixel->s = 1.0;
      pixel->l = .5;
      pixel->a = 1.0;
    }
  }

  for(unsigned int j = height*3/8; j<(height*5/8);j++)
  {
    for(unsigned int i=(width*3/8);i<(width*5/8);i++)
    {
      HSLAPixel *pixel = png.getPixel(i,j);
      pixel->h = 22;
      pixel->s = 1.0;
      pixel->l = .5;
      pixel->a = 1.0;
    }
  }

  for(unsigned int j = height*5/8; j<(height*7/8);j++)
  {
    for(unsigned int i=(width/8);i<(width*7/8);i++)
    {
      HSLAPixel *pixel = png.getPixel(i,j);
      pixel->h = 22;
      pixel->s = 1.0;
      pixel->l = .5;
      pixel->a = 1.0;
    }
  }
  */

  return png;
}
