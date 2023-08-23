#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define FENNEC_INCLUDE_EVERYTHING
#include "../fennec/fennec.h"

int main(void) {
    if (fennec_get_version() != FENNEC_V1) {
        fennec_log_error("Incorrect version of fennec - requires v1");
        return 1;
    }

    FennecWindow win;
    fennec_init();

    fennec_window_init(&win, 1280, 720, "Test");
    fennec_glew_init();

    // not ripped from learnopengl i promise
    // screen quad
    float quadVertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(quadVertices),
        &quadVertices,
        GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        (void*)(2 * sizeof(float)));

    // testing shaders
    FennecShader *shader = fennec_shader_new(
            "test/vertex.glsl",
            "test/fragment.glsl");
    FennecShader *fbshader = fennec_shader_new(
            "test/vertex_framebuffer.glsl",
            "test/fragment_framebuffer.glsl");
    // testing textures
    FennecTexture *texture = fennec_texture_new(
        "test/test_texture.png",
        GL_RGBA);
    FennecFramebuffer *framebuffer = fennec_framebuffer_new(320, 160);

    fennec_shader_use(shader);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    while (!glfwWindowShouldClose(win.window)) {
        fennec_framebuffer_use(framebuffer);
        fennec_shader_use(shader);
        glViewport(0, 0, framebuffer->width, framebuffer->height);
        glBindVertexArray(quadVAO);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        int w;
        int h;
        glfwGetWindowSize(win.window, &w, &h);
        glViewport(0, 0, w, h);
        fennec_shader_use(fbshader);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(quadVAO);
        glBindTexture(GL_TEXTURE_2D, framebuffer->texture->id);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(win.window);
        glfwPollEvents();
    }

    fennec_shader_free(shader);
    fennec_shader_free(fbshader);
    fennec_texture_free(texture);
    fennec_framebuffer_free(framebuffer);

    glfwTerminate();
    return 0;
}
