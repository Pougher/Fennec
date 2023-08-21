#include "shader.h"

FennecShader *fennec_shader_new(char *vs, char *fs) {
    FennecShader *new_shader = malloc(sizeof(FennecShader));
    new_shader->id = 0;

    const char* vshader_code = fennec_read_file(vs);
    const char* fshader_code = fennec_read_file(fs);
    if (vshader_code == NULL || fshader_code == NULL) {
        fennec_log_error("Cannot generate shader - files missing");
        return new_shader;
    }

    unsigned int vertex;
    unsigned int fragment;
    int success;
    char info[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vshader_code, NULL);
    glCompileShader(vertex);

    // check if there are any errors, and if there are, print them
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, info);
        fennec_log_error(info);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fshader_code, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, info);
        fennec_log_error(info);
    }
    // now link the two shaders and generate a program
    new_shader->id = glCreateProgram();
    glAttachShader(new_shader->id, vertex);
    glAttachShader(new_shader->id, fragment);
    glLinkProgram(new_shader->id);

    // output any linking errors
    glGetProgramiv(new_shader->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(new_shader->id, 512, NULL, info);
        fennec_log_error(info);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free((char*)vshader_code);
    free((char*)fshader_code);
#ifndef FENNEC_NO_LOGS
    char shader_log_msg[strlen(fs) + strlen(vs) + 128];
    sprintf(
        shader_log_msg,
        "Generated shader %d from '%s' and '%s'",
        new_shader->id,
        vs,
        fs);
    fennec_log_info(shader_log_msg);
#endif
    return new_shader;
}

void fennec_shader_use(FennecShader *shader) {
    glUseProgram(shader->id);
}

void fennec_shader_free(FennecShader *shader) {
    glDeleteProgram(shader->id);
    free(shader);
}

void fennec_shader_setbool(FennecShader *shader, const char *name, bool val) {
    glUniform1i(glGetUniformLocation(shader->id, name), val);
}

void fennec_shader_setint(FennecShader *shader, const char *name, int val) {
    glUniform1i(glGetUniformLocation(shader->id, name), val);
}

void fennec_shader_setfloat(FennecShader *shader, const char *name, float val) {
    glUniform1f(glGetUniformLocation(shader->id, name), val);
}
