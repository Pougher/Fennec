#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tc;

out vec2 texcoord;

void main() {
    gl_Position = vec4(pos, 1.0);
    texcoord = tc;
}
