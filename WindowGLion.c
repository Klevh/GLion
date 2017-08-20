#include "WindowGLion.h"

typedef struct ListElementGLion ListElementGLion;

struct WindowGLion{
    GLFWwindow         * window;
    int                  height;
    int                  width;
    int                  initHeight;
    int                  initWidth;
    int                  displayCode;
    int                  background[4];
    unsigned             toDelete; /*number of elements to delete*/
    int                  close; /*tells whether or not the window should be closed*/
    ListElementGLion   * elements;
    struct WindowGLion * next;
};

WindowGLion * _windows_GLION = NULL;
