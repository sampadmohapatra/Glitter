#version 400 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vInTexCoord;

out vec2 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(vPos, 1.0f);
    vTexCoord = vInTexCoord;
}