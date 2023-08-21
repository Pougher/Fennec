#ifndef FENNEC_SHADER_H
#define FENNEC_SHADER_H

/* NOTE:
 * If you want to disable shader generation logs, put this before you include
 * this file: #define FENNEC_NO_LOGS
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "log.h"
#include "fileio.h"

typedef struct {
    // the ID of the shader
    unsigned int id;
} FennecShader;

/*
 * @description
 * Creates a new FennecShader object allocated on the heap, meaning it must
 * be freed later. It automatically generates a shader ID that can be used by
 * OpenGL while rendering.
 *
 * @argument
 * The vertex shader that will be compiled
 *
 * @argument
 * The fragment shader that will be compiled
 *
 * @returns
 * A new shader object which can be used in OpenGL with `fennec_shader_use`
 */
FennecShader* fennec_shader_new(char*, char*);

/* @description
 * Tells OpenGL to bind a shader
 */
void fennec_shader_use(FennecShader*);

/* @description
 * Destroys the OpenGL program ID and then frees the data allocated to the
 * shader on the stack
 */
void fennec_shader_free(FennecShader*);

/* SENDING DATA TO SHADERS */

/* @description
 * Sends a boolean to the provided shader
 */
void fennec_shader_setbool(FennecShader*, const char*, bool);

/* @description
 * Sends an integer to the provided shader
 */
void fennec_shader_setint(FennecShader*, const char*, int);

/* @description
 * Sends a float to the provided shader
 */
void fennec_shader_setfloat(FennecShader*, const char*, float);
#endif
