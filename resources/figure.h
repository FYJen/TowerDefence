/*
 * Figure class that all monster and play inherit from.
 */
#ifndef FIGURE_H
#define FIGURE_H

/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class Displayable {
    public:
        virtual void paint(XInfo &xinfo) = 0;
};

#endif
