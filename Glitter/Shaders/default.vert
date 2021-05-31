#version 400 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vInCol;
layout (location = 2) in vec2 vInTexCoord;

out vec3 vCol;
out vec2 vTexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(vPos, 1.0f);
    vCol = vInCol;
    vTexCoord = vInTexCoord;
}