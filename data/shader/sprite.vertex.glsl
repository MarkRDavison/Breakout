#version 410 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Color;
layout(location = 2) in vec2 in_TexUV;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

out vec4 fragColor;
out vec2 texUV;

void main() {
    gl_Position = projection * view * model * vec4(in_Position, 1.0);
    fragColor = in_Color;
    texUV = in_TexUV;
}