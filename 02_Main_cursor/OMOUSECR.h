#ifndef __OMOUSECR_H
#define __OMOUSECR_H

class MouseCursor{
/* [1] - fields */
private:
public:
    char *save_scr, *save_back_scr, *merge_buf;
    int cur_x1, cur_y1, cur_x2, cur_y2;
    int hot_spot_x, hot_spot_y;
    int icon_width, icon_height;
    char *icon_ptr;
    char cursor_shown;
/* [2] - methods */
private:
public:
    void init();
    void process(int curX, int curY);
};

extern MouseCursor mouse_cursor;

#endif
