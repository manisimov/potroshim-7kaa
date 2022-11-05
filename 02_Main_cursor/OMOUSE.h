#ifndef __OMOUSE_H
#define __OMOUSE_H

class Mouse{
/* [1] - Fields */
private:
public:
    int cur_x;
    int cur_y;
/* [2] - Methods */
private:
public:
    void init();
    void process_mouse_motion(int x, int y);
};

extern Mouse mouse;

#endif
