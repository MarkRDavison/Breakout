#version 410 core

in vec4 fragColor;
in vec2 texUV;

uniform sampler2D tex;
out vec4 FragColor;

void main() {
    FragColor = texture(tex, texUV) * fragColor;
}