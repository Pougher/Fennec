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

    float vertices[] = {
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // testing shaders
    FennecShader* shader = fennec_shader_new(
            "test/vertex.glsl",
            "test/fragment.glsl");

    // testing textures
    FennecTexture* texture = fennec_texture_new("test/test_texture.png");

    fennec_shader_use(shader);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(win.window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(win.window);
        glfwPollEvents();
    }

    fennec_shader_free(shader);
    fennec_texture_free(texture);

    glfwTerminate();
    return 0;
}
