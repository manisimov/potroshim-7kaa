#include <stdio.h>
#include "OSYS.h"
#include "OVGA.h"
#include "OVGABUF.h"
#include "OMOUSECR.h"
#include "OMOUSE.h"

Sys::Sys()
{
}

Sys::~Sys()
{
}

int Sys::init()
{
    init_directx();
    init_objects();

    return 1;
}

int Sys::init_directx()
{
    vga.init();
    vga_front.init(1);

    return 1;
}

int Sys::init_objects()
{
    mouse_cursor.init();
    mouse.init();

    return 1;
}

void Sys::yield()
{
    vga.handle_messages();
}

void Sys::deinit()
{
}
