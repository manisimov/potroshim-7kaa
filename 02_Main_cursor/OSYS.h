#ifndef __OSYS_H
#define __OSYS_H

class Sys
{
private:
public:
    char signal_exit_flag;
private:
    int init_directx();
    int init_objects();
public:
    Sys();
    ~Sys();
    int init();
    void deinit();
    void yield();
};

extern Sys sys;

#endif
