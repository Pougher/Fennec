#include "window.h"

void fennec_window_init(
    FennecWindow *win,
    int w,
    int h,
    char *name) {
    win->window = glfwCreateWindow(w, h, name, NULL, NULL);

    if (win->window == NULL) {
        fennec_log_error("Could not initialize window context");
        glfwTerminate();
    }
    glfwMakeContextCurrent(win->window);
}
