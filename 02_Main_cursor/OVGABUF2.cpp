#include "OVGABUF.h"
#include <string.h>

#define TRANSPARENT_CODE 0xFF

void VgaBuf::bar(int x1, int y1, int x2, int y2, int colorCode)
{
    char *imageBuf = buf_ptr();
    int   pitch    = buf_pitch();
    int   dest     = y1 * pitch + x1;
    int   width    = x2 - x1 + 1;

    for(int y = y1; y <= y2; ++y, dest += pitch)
    {
        memset(&imageBuf[dest], colorCode, width);
    }
}

void  VgaBuf::put_bitmap_area_trans(int desX, int desY,char* bitmapPtr,int srcX1, int srcY1, int srcX2, int srcY2)
{
    char *imageBuf = buf_ptr();
    int   pitch    = buf_pitch();
    char *bitmapBuf = bitmapPtr;

    int destline = (desY+srcY1)*pitch + (desX+srcX1);
    int bitmapWidth = ((unsigned char*)bitmapBuf)[0] + (((unsigned char*)bitmapBuf)[1]<<8);
    int width = srcX2 - srcX1 + 1;
    int height = srcY2 - srcY1 + 1;
    int esi = 4 + srcY1 * bitmapWidth + srcX1;

    for(int j = 0; j < height; ++j, destline += pitch, esi += bitmapWidth)
    {
        for(int i=0; i<width; ++i)
        {
            if( ((unsigned char*)bitmapBuf)[esi + i] != TRANSPARENT_CODE )
            {
                imageBuf[destline + i] = bitmapBuf[esi+i];
            }
        }
    }
}

void VgaBuf::read_bitmap(int x1,int y1,int x2,int y2, char* bitmapPtr)
{
    char *imageBuf = buf_ptr();
    int   pitch    = buf_pitch();

    int width = x2 - x1 + 1;
    int height = y2 - y1 + 1;
    int offset;
    int src_offset;

    ((unsigned char*)bitmapPtr)[0] = width & 0xff;
    ((unsigned char*)bitmapPtr)[1] = width>>8;
    ((unsigned char*)bitmapPtr)[2] = height & 0xff;
    ((unsigned char*)bitmapPtr)[3] = height>>8;
    offset = 4;
    src_offset = y1 * pitch + x1;
    for(int y = 0; y < height; ++y)
    {
        memcpy(&bitmapPtr[offset], &imageBuf[src_offset], width);
        offset += width;
        src_offset += pitch;
    }
}
