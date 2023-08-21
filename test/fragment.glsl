#version 410 core

out vec4 frag_color;

in vec4 color;

void main() {
    frag_color = color;
}
