#ifndef __OVGABUF_H
#define __OVGABUF_H

#include <SDL.h>

class VgaBuf{
/* [1] - Fields */
public:
    SDL_Surface  *surface;
    char         *cur_buf_ptr;
private:
/* [2] - Methods */
public:
    int   init(char front, int w=0, int h=0);
    char *buf_ptr()   { return cur_buf_ptr; }
    int   buf_pitch() { return surface->pitch; }
    void  bar(int x1, int y1, int x2, int y2, int colorCode);
    void  put_bitmap_area_trans(int desX, int desY,char *bitmapPtr,int srcX1, int srcY1, int srcX2, int srcY2);
    void read_bitmap(int x1,int y1,int x2,int y2, char *bitmapPtr);
private:

};

extern VgaBuf vga_front;

#endif
