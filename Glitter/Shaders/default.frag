#version 400 core

in vec2 vTexCoord;

out vec4 vFragColor;

uniform sampler2D sqTex1;
uniform sampler2D sqTex2;

void main() {
    vFragColor = mix(texture(sqTex1, vTexCoord),
                     texture(sqTex2, vTexCoord), 0.2);
}