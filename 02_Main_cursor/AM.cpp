#include <stdio.h>

#include "OSYS.h"
#include "OVGA.h"
#include "OVGABUF.h"
#include "OMOUSECR.h"
#include "OMOUSE.h"
#include "OGAME.h"

Sys          sys;
Vga          vga;
VgaBuf       vga_front;
MouseCursor  mouse_cursor;
Mouse        mouse;
Game         game;

int main(void)
{
    sys.init();
    game.main_menu();
    sys.deinit();
}
