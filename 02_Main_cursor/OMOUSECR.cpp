#include "OMOUSECR.h"
#include "ALL.h"
#include "OVGA.h"
#include "OVGABUF.h"
#include <string.h>

#define CURSOR_HEIGHT 64
#define CURSOR_WIDTH  128


void MouseCursor::init()
{
    // Read cursor bitmap from a file?
    // Just generate it for now
    icon_ptr = (char*)malloc(CURSOR_HEIGHT * CURSOR_WIDTH + 2 * sizeof(short));
    memset(icon_ptr, 0x02, CURSOR_HEIGHT * CURSOR_WIDTH + 2 * sizeof(short));
    memset(icon_ptr + 4 + 10 * CURSOR_WIDTH, 0xFF, 30 * CURSOR_WIDTH);
    *(short*)icon_ptr = CURSOR_WIDTH;
    *((short*)icon_ptr + 1) = CURSOR_HEIGHT;
    //

    hot_spot_x = 0;
    hot_spot_y = 0;
    icon_width = *(short*)icon_ptr;
    icon_height = *((short*)icon_ptr + 1);

    save_scr = (char*)malloc(CURSOR_HEIGHT * CURSOR_WIDTH + 2 * sizeof(short));

    process(0, 0);
}

void MouseCursor::process(int curX, int curY)
{
    int save_x1, save_x2, save_y1, save_y2;

    save_x1 = MAX(cur_x1, 0);
    save_y1 = MAX(cur_y1, 0);
    save_x2 = MIN(cur_x2, VGA_WIDTH - 1);
    save_y2 = MIN(cur_y2, VGA_HEIGHT - 1);

    if(cursor_shown)
    {
        if(save_x1 < save_x2 && save_y1 < save_y2)
        {
            /* Move previously saved bitmap under the cursor
             * to the vga object bitmap.
             * Also consider the case when mouse coordinates are
             * outside of the screen.
             */
            vga_front.put_bitmap_area_trans( save_x1,
                                             save_y1,
                                             save_scr,
                                             save_x1 - cur_x1,
                                             save_y1 - cur_y1,
                                             save_x2 - cur_x1,
                                             save_y2 - cur_y1);
        }
    }

    cur_x1 = curX - hot_spot_x;
    cur_y1 = curY - hot_spot_y;
    cur_x2 = cur_x1 + icon_width - 1;
    cur_y2 = cur_y1 + icon_height - 1;

    save_x1 = MAX(cur_x1, 0);
    save_y1 = MAX(cur_y1, 0);
    save_x2 = MIN(cur_x2, VGA_WIDTH - 1);
    save_y2 = MIN(cur_y2, VGA_HEIGHT - 1);

    if(save_x1 < save_x2 && save_y1 < save_y2)
    {
        /* Save bitmap under the cursor on a new position */
        vga_front.read_bitmap(save_x1, save_y1, save_x2, save_y2, save_scr);

        /* Draw cursor on a new position */
        vga_front.put_bitmap_area_trans( save_x1,
                                         save_y1,
                                         icon_ptr,
                                         save_x1 - cur_x1,
                                         save_y1 - cur_y1,
                                         save_x2 - cur_x1,
                                         save_y2 - cur_y1);
        cursor_shown = 1;
    }
}
