#include "texture.h"

FennecTexture *fennec_texture_new(char *filename) {
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
        GL_RGBA,
        new_texture->width,
        new_texture->height,
        0,
        GL_RGBA,
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

void fennec_texture_free(FennecTexture *texture) {
    glDeleteTextures(1, &texture->id);
    free(texture);
}
