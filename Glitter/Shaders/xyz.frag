#version 400 core

in vec3 vVertCol;

out vec4 vFragColor;

void main() {
    vFragColor = vec4(vVertCol, 1.0);
}