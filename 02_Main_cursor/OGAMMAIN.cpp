#include "OGAME.h"
#include "OVGABUF.h"
#include "OVGA.h"
#include "OSYS.h"

void Game::main_menu()
{
    int refreshFlag = 1;

    vga_front.bar(0, 0, VGA_WIDTH - 1, VGA_HEIGHT - 1, 0);

    while(1)
    {
        if(refreshFlag)
        {
            int sq = 150;
            // Make back ground image. Three rectangles.
            vga_front.bar(sq, sq, VGA_WIDTH - sq - 1, VGA_HEIGHT - sq - 1, 1);
            sq = 200;
            vga_front.bar(sq, sq, VGA_WIDTH - sq - 1, VGA_HEIGHT - sq - 1, 3);
            sq = 250;
            vga_front.bar(sq, sq, VGA_WIDTH - sq - 1, VGA_HEIGHT - sq - 1, 4);
        }

        sys.yield();
        vga.flip();
        refreshFlag = 0;

        if(sys.signal_exit_flag == 1)
            break;
    }
}
