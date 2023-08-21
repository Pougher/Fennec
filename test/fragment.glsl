#version 410 core

out vec4 frag_color;
in vec2 texcoord;

uniform sampler2D tex;

void main() {
    frag_color = texture(tex, texcoord);
}
