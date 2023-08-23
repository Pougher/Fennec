#ifndef FENNEC_FRAMEBUFFER_H
#define FENNEC_FRAMEBUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "texture.h"

/* NOTE:
 * If you want to disable framebuffer generation logs, put this before you
 * include this file: #define FENNEC_NO_LOGS
 */

typedef struct {
    // the framebuffer object
    unsigned int fbo;

    // renderbuffer attachment to the framebuffer
    unsigned int rbo;

    // width of the framebuffer
    int width;

    // height of the framebuffer
    int height;

    // the texture attachment for the framebuffer
    FennecTexture *texture;
} FennecFramebuffer;

/*
 * @description
 * Creates a new OpenGL framebuffer object and attaches a renderbuffer and a
 * texture. This means it can be rendered to. To ensure resources are freed
 * correctly, call `fennec_framebuffer_free` when you are done using the
 * framebuffer
 *
 * @argument
 * The width of the framebuffer
 *
 * @argument
 * The height of the framebuffer
 */
FennecFramebuffer *fennec_framebuffer_new(int, int);

/*
 * @description
 * Instructs OpenGL to set the current framebuffer to the framebuffer provided
 */
void fennec_framebuffer_use(FennecFramebuffer*);

/*
 * @description
 * Deletes a framebuffers fbo, rbo and texture objects
 * Only use when your framebuffer is no longer in use
 */
void fennec_framebuffer_free(FennecFramebuffer*);

#endif
