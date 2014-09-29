#ifndef WINDOW_H
#define WINDOW_H

#include <map>

/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

/*
 * Information to draw on the window.
 */
struct XInfo {
    Display *display;
    int screen;
    Window window;
    GC gc[2];
    XFontStruct *font;
    Pixmap pixmap;
    int width;
    int height;
};

void initX(int argc, char* argv[], XInfo& xInfo);

#endif
