#ifndef FENNEC_WINDOW_H
#define FENNEC_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "log.h"

typedef struct {
    // the pointer to the GLFW window
    GLFWwindow *window;
} FennecWindow;


/*
 * @description
 * Initializes a Fennec_Window by creating a window context
 *
 * @argument: the window that is to be initialized
 * @argument: the width of the window context
 * @argument: the height of the window context
 * @argument: the name of the window context
 */
void fennec_window_init(FennecWindow*, int, int, char*);

#endif
