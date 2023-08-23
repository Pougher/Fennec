#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

FennecTexture *fennec_texture_new(char *filename, GLuint format) {
    stbi_set_flip_vertically_on_load(1);
    FennecTexture *new_texture = malloc(sizeof(FennecTexture));

    unsigned char *data = stbi_load(
        filename,
        &new_texture->width,
        &new_texture->height,
        &new_texture->channels,
        0);

    if (data == NULL) {
        char error_msg[32 + strlen(filename)];
        sprintf(error_msg, "Error loading texture '%s'", filename);
        fennec_log_error(error_msg);

        new_texture->id = 0;
        return new_texture;
    }

    // generate the OpenGL texture
    glGenTextures(1, &new_texture->id);
    glBindTexture(GL_TEXTURE_2D, new_texture->id);

    // set the texture attributes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // now that the texture is bound, we can start to generate it from the
    // previously loaded image data
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        new_texture->width,
        new_texture->height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // free the stb image data
    free(data);

#ifndef FENNEC_NO_LOGS
    // UNSAFE
    char buffer[512 + strlen(filename)];
    sprintf(
        buffer,
        "Generated texture ID %d for '%s' with dimensions %dx%d",
        new_texture->id,
        filename,
        new_texture->width,
        new_texture->height);
    fennec_log_info(buffer);
#endif

    return new_texture;
}

FennecTexture *fennec_texture_empty(int width, int height, GLuint format) {
    FennecTexture *new_shader = malloc(sizeof(FennecTexture));

    switch (format) {
        case GL_RGB: { new_shader->channels = 3; break; }
        case GL_RGBA: { new_shader->channels = 4; break; }
        default: {
            fennec_log_error(
                "Unsupported format passed to fennec_texture_empty");
            break;
        }
    }
    new_shader->width = width;
    new_shader->height = height;

    // generate an empty data array
    unsigned char *empty = calloc(new_shader->channels, width * height);

    glGenTextures(1, &new_shader->id);
    glBindTexture(GL_TEXTURE_2D, new_shader->id);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        empty);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    free(empty);

    return new_shader;
}


void fennec_texture_free(FennecTexture *texture) {
    glDeleteTextures(1, &texture->id);
    free(texture);
}
