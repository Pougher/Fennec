#include "fennec.h"

int fennec_get_version(void) {
    return FENNEC_VERSION;
}

void fennec_init(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, FENNEC_GL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, FENNEC_GL_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void fennec_glew_init(void) {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fennec_log_error("Failed to initialize GLEW");
        glfwTerminate();
        exit(1);
    }
}
