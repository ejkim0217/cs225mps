#include "StickerSheet.h"
#include "Image.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max){
  //Makes the base pointer have the picture image value
  base_ = new Image();
  *base_ = picture;
  //Creates an array of pointers and x/y arrays to keep track of positions
  max_ = max;
  arr_ = new Image*[max_];
  xarr_ = new unsigned [max_];
  yarr_ = new unsigned [max_];
  for(unsigned i=0; i<max_; i++){
    arr_[i] = NULL;
    xarr_[i] = 0;
    yarr_[i] = 0;
  }
}

StickerSheet::StickerSheet(const StickerSheet &other){
  max_ = other.max_;
  base_ = new Image();
  *base_ = *(other.base_);
  arr_ = new Image*[max_];
  xarr_ = new unsigned [max_];
  yarr_ = new unsigned [max_];
  for(unsigned i=0; i<max_;i++)
  {
    arr_[i] = other.arr_[i];
    xarr_[i] = other.xarr_[i];
    yarr_[i] = other.yarr_[i];
  }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other)
{
  if(this != &other){
  delete base_;
  delete[] arr_; arr_ = NULL;
  delete[] xarr_; xarr_ = NULL;
  delete[] yarr_; yarr_ = NULL;
  //Showing the implicit this pointer helps show difference between copy
  //and assignment operator
  max_ = other.max_;
  base_ = new Image();
  *base_ = *(other.base_);
  arr_ = new Image*[max_];
  xarr_ = new unsigned [max_];
  yarr_ = new unsigned [max_];
  for(unsigned i=0; i<max_;i++)
  {
    arr_[i] = other.arr_[i];
    xarr_[i] = other.xarr_[i];
    yarr_[i] = other.yarr_[i];
  }
}
  return *this;
}


int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  if(x<base_->width() && y<base_->height()){
    int flag =0;
    for(unsigned i=0; i<max_; i++){
      if(arr_[i] == NULL)
      {
        arr_[i] = &sticker;
        xarr_[i] = x;
        yarr_[i] = y;
        flag =i;
        break;
      }
    }
  return flag;
  }
  else
    return -1;
}

//done
void StickerSheet::changeMaxStickers(unsigned max){
  //Create temp array to hold everything
  Image** temp = new Image*[max];
  unsigned* x_temp = new unsigned [max];
  unsigned* y_temp = new unsigned [max];
  unsigned max_value = (max < max_) ? max:max_;
  for(unsigned i=0;i<max_value;i++){
    temp[i] = arr_[i];
    x_temp[i] = xarr_[i];
    y_temp[i] = yarr_[i];
  }
  //Either deletes are wrong or shallow copies don't hold
  delete[] arr_;
  delete[] xarr_;
  delete[] yarr_;
  //Recreate pointer with new max sticker range
  arr_ = temp;
  xarr_ = x_temp;
  yarr_ = y_temp;
  max_ = max;
}

//done
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
  if(x+xarr_[index]>base_->width() || y+yarr_[index]>base_->height())
    return false;
  if(arr_[index] == NULL)
    return false;
  xarr_[index] = x;
  yarr_[index] = y;
  return true;
}
//done
void StickerSheet::removeSticker(unsigned index){
  arr_[index]=NULL;
  xarr_[index] = 0;
  yarr_[index] = 0;
}
//done
Image* StickerSheet::getSticker(unsigned index) const{
  if(index < max_)
    return arr_[index];
  else
    return NULL;
}

Image StickerSheet::render() const{
  //Figure out size of image
  unsigned max_width= base_->width();
  unsigned max_height= base_->height();
  for(unsigned i=0; i<max_;i++){
    if(arr_[i] != NULL){
      unsigned temp_max_width = arr_[i]->width() + xarr_[i];
      unsigned temp_max_height = arr_[i]->height() + yarr_[i];
      if(temp_max_width > max_width)
        max_width = temp_max_width;
      if(temp_max_height > max_height)
        max_height = temp_max_height;
    }
  }
  //Puts in background image
  Image *render = new Image();
  render->resize(max_width, max_height);
  for(unsigned x=0; x<base_->width(); x++){
    for(unsigned y=0; y<base_->height(); y++){
      render->getPixel(x,y) = base_->getPixel(x,y);
    }
  }


  for(unsigned i=0; i<max_;i++){
    if(arr_[i] != NULL){
      for(unsigned x=0; x<arr_[i]->width(); x++){
        for(unsigned y=0; y<arr_[i]->height(); y++){
          cs225:: HSLAPixel &oldPixel = render->getPixel((x+xarr_[i]),(y+yarr_[i]));
          cs225:: HSLAPixel &newPixel = arr_[i]->getPixel(x,y);
          if(newPixel.a != 0){
            oldPixel = newPixel;
          }
        }
      }
    }
  }
  return *render;
}

StickerSheet::~StickerSheet(){
  /*for(unsigned i=0; i<max_;i++){
    if(arr_[i] !=NULL){
    delete arr_[i];
    }
  }*/
  delete[] xarr_;
  delete[] yarr_;
  delete[] arr_;
  delete base_;
}
