/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_
#include "Image.h"

class StickerSheet{

public:
  //Constructors and Rule of Three
  StickerSheet(const Image &picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet &other);
  const StickerSheet &operator=(const StickerSheet &other);

  //Interesting functions
  void changeMaxStickers(unsigned max);
  int addSticker(Image &sticker, unsigned x, unsigned y);
  bool translate (unsigned index, unsigned x, unsigned y);
  void removeSticker(unsigned index);
  Image *getSticker(unsigned index) const;
  Image render() const;
private:
  Image* base_;
  Image** arr_;
  unsigned* xarr_;
  unsigned* yarr_;
  unsigned max_;
};

#endif

/*THOMAS -- Need to finish copy constructor and operator function
*/
