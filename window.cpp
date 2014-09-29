#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <map>

/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "resources/window.h"
#include "resources/helper.h"
#include "resources/config.h"

using namespace std;

/*
 * Create a window
 */
void initX(int argc, char *argv[], XInfo &xinfo) {
    XSizeHints hints;
    unsigned long white, black;

   /*
    * Display opening uses the DISPLAY  environment variable.
    * It can go wrong if DISPLAY isn't set, or you don't have permission.
    */  
    xinfo.display = XOpenDisplay( "" );
    if ( !xinfo.display )   {
        error( "Can't open display." );
    }
    
   /*
    * Find out some things about the display you're using.
    */
    xinfo.screen = DefaultScreen( xinfo.display );

    white = XWhitePixel( xinfo.display, xinfo.screen );
    black = XBlackPixel( xinfo.display, xinfo.screen );

    hints.x = 100;
    hints.y = 100;
    hints.width = 1000;
    hints.height = 600;
    hints.flags = PPosition | PSize;

    xinfo.window = XCreateSimpleWindow( 
        xinfo.display,              // display where window appears
        DefaultRootWindow( xinfo.display ), // window's parent in window tree
        hints.x, hints.y,           // upper left corner location
        hints.width, hints.height,  // size of the window
        Border,                     // width of window's border
        white,                      // window border colour
        black );                    // window background colour
        
    XSetStandardProperties(
        xinfo.display,       // display containing the window
        xinfo.window,        // window whose properties are set
        "Tower Defense",     // window's title
        "TD",                // icon's title
        None,                // pixmap for the icon
        argv, argc,          // applications command line args
        &hints );            // size hints for the window

    /* 
     * Create Graphics Contexts
     */
    int key = 0;
    xinfo.gc[key] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XSetForeground(xinfo.display, xinfo.gc[key],
                   BlackPixel(xinfo.display, xinfo.screen));
    XSetBackground(xinfo.display, xinfo.gc[key],
                   WhitePixel(xinfo.display, xinfo.screen));
    XSetFillStyle(xinfo.display, xinfo.gc[key], FillSolid);
    XSetLineAttributes(xinfo.display, xinfo.gc[key], 1, LineSolid, CapButt, JoinRound);
    XSetGraphicsExposures(xinfo.display, xinfo.gc[key], false);

    key = 1;
    xinfo.gc[key] = XCreateGC(xinfo.display, xinfo.window, 0, 0);
    XSetForeground(xinfo.display, xinfo.gc[key],
                   WhitePixel(xinfo.display, xinfo.screen));
    XSetBackground(xinfo.display, xinfo.gc[key],
                   BlackPixel(xinfo.display, xinfo.screen));
    XSetFillStyle(xinfo.display, xinfo.gc[key], FillSolid);
    XSetLineAttributes(xinfo.display, xinfo.gc[key], 1, LineSolid, CapButt, JoinRound);
    XSetGraphicsExposures(xinfo.display, xinfo.gc[key], false);

    int depth = DefaultDepth(xinfo.display, DefaultScreen(xinfo.display));
    xinfo.pixmap = XCreatePixmap(xinfo.display, xinfo.window, hints.width,
                                 hints.height, depth);
    xinfo.width = hints.width;
    xinfo.height = hints.height;

    XSelectInput(xinfo.display, xinfo.window, 
        ButtonPressMask | KeyPressMask | KeyReleaseMask | PointerMotionMask
        | EnterWindowMask | LeaveWindowMask
        | StructureNotifyMask   // for resize events
        );

    /*
     * Don't paint the background -- reduce flickering
     */
    XSetWindowBackgroundPixmap(xinfo.display, xinfo.window, None);

    /*
     * Turn keyboard auto repeat off.
     */
    XAutoRepeatOff(xinfo.display);

    /*
     * Set Font.
     */
    xinfo.font = XLoadQueryFont (xinfo.display, "fixed");
    XSetFont(xinfo.display, xinfo.gc[0], xinfo.font->fid);

    /*
     * Put the window on the screen.
     */
    XMapRaised( xinfo.display, xinfo.window);
    
    XFlush(xinfo.display);
    sleep(3);   // let server get set up before sending drawing commands
}
