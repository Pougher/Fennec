#ifndef FENNEC_H
#define FENNEC_H

// the version of fennec source code
static const int FENNEC_VERSION = 1;

// version names to simplify things
#define FENNEC_V1 1

// OpenGL major and minor versions
#define FENNEC_GL_MAJOR 4
#define FENNEC_GL_MINOR 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// headers within fennec that fennec.c requires
#include "log.h"

#ifdef FENNEC_INCLUDE_EVERYTHING

#include "window.h"
#include "shader.h"
#include "fileio.h"
#include "dynarray.h"
#include "texture.h"
#include "framebuffer.h"

#endif

/*
 * @description
 * Returns the current version of fennec, such that if in the future
 * an update adds certain functions, code that relies off of those
 * functions can determine if their version of fennec supports them
 */
int fennec_get_version(void);

/*
 * @description
 * Initializes GLFW, and sets the OpenGL major and minor versions. If
 * you are on a mac, then it also sets GLFW_OPENGL_FORWARD_COMPAT.
 * The major and minor version of OpenGL may be changed by modifying
 * the FENNEC_GL_MAJOR and FENNEC_GL_MINOR macros
 */
void fennec_init(void);

/*
 * @description
 * Initializes GLEW. This should only be done once, but must be done
 * after a context has been made current
 */
void fennec_glew_init(void);

#endif
