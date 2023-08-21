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

    fennec_window_init(&win, 1280, 720, "Fennec Test");
    fennec_glew_init();

    // testing shaaders
    FennecShader* shader = fennec_shader_new(
            "test/vertex.glsl",
            "test/fragment.glsl");

    while (!glfwWindowShouldClose(win.window)) {
        glfwSwapBuffers(win.window);
        glfwPollEvents();
    }

    fennec_shader_free(shader);

    glfwTerminate();
    return 0;
}
