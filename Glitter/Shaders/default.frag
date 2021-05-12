#version 400 core

in vec3 vCol;
in vec2 vTexCoord;

out vec4 vFragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixFactor;

void main()
{
    vFragColor = mix(texture(texture1, vTexCoord), texture(texture2, vTexCoord), mixFactor);
//    vFragColor = texture(texture1, vTexCoord);
}