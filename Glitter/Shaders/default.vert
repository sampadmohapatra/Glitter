#version 400 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vInCol;
layout (location = 2) in vec2 vInTexCoord;
layout (location = 3) in vec3 vCirclePos;
layout (location = 4) in vec3 vInCircleCol;

out vec3 vCol;
out vec3 vCircleCol;
out vec2 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform bool bDrawCircle;

void main()
{
    if(!bDrawCircle)
        gl_Position = projection * view * model * vec4(vPos, 1.0f);
    else
        gl_Position = projection * view * model * vec4(vCirclePos, 1.0f);
    vCol = vInCol;
    vCircleCol = vInCircleCol;
    vTexCoord = vInTexCoord;
}