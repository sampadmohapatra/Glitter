#version 400 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vInCol;
layout (location = 2) in vec2 vInTexCoord;

out vec3 vCol;
out vec2 vTexCoord;

void main()
{
    gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0);
    vCol = vInCol;
    vTexCoord = vInTexCoord;
}