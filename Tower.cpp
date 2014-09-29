/*
Commands to compile and run:

    g++ -o Tower Tower.cpp -L/usr/X11R6/lib -lX11 -lstdc++
    ./Tower

Note: the -L option and -lstdc++ may not be needed on some machines.

*/

#include <iostream>
#include <cstdlib>
#include <unistd.h>

/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/*
 * Header files for custon resources.
 */
#include "resources/window.h"
#include "resources/environment.h"
#include "resources/config.h"

using namespace std;

void guidelineLoop(Environment *env) {
    XEvent event;
    XInfo &xInfo = env->getXInfo();

    bool proceed = false;
    while (true && !proceed) {
        if (XPending(xInfo.display) > 0) {
            XNextEvent(xInfo.display, &event);
            switch(event.type) {
                case KeyRelease: {
                    env->handleKeyReleaseBeforeAfterGame(event, proceed);
                    break;
                }
                case ConfigureNotify: {
                    env->handleResize(event);
                    break;
                }
            }
        }
        usleep(1000000/FPS);
        env->paintGuideline();
    }
}

void gameOverLoop(Environment *env) {
    XEvent event;
    XInfo &xInfo = env->getXInfo();

    bool proceed = false;
    while (true && !proceed) {
        if (XPending(xInfo.display) > 0) {
            XNextEvent(xInfo.display, &event);
            switch(event.type) {
                case KeyRelease: {
                    env->handleKeyReleaseBeforeAfterGame(event, proceed);
                    break;
                }
                case ConfigureNotify: {
                    env->handleResize(event);
                    break;
                }
            }
        }
        usleep(1000000/FPS);
        env->paintGameOver();
    }
}

void eventLoop(Environment *env) {
    XEvent event;
    XInfo &xInfo = env->getXInfo();

    while (!env->hasGameEnded()) {
        if (XPending(xInfo.display) > 0) {
            XNextEvent(xInfo.display, &event);
            switch(event.type) {
                case KeyPress:
                    env->handleKeyPress(event);
                    break;
                case KeyRelease:
                    env->handleKeyRelease(event);
                    break;
                case EnterNotify:
                    env->setIsMouseInside(true);
                    break;
                case LeaveNotify:
                    env->setIsMouseInside(false);
                    break;
                case ConfigureNotify:
                    env->handleResize(event);
                    break;
            }
        }

        usleep(1000000/FPS);
        env->handleAnimation();
        env->paint();
    }

}

/*
 * Main
 */
int main ( int argc, char* argv[] ) {
    XInfo xInfo;

    initX(argc, argv, xInfo);

    // Initialize environment.
    Environment *env = new Environment(xInfo);

    // Intro with guideline.
    guidelineLoop(env);

    // Start the game loop.
    eventLoop(env);

    // Game ends.
    gameOverLoop(env);
    env->gameEnds();
    delete env;
    XCloseDisplay(xInfo.display);
}
