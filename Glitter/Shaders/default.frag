#version 330 core

in vec3 vCol;
out vec4 vFragColor;

void main()
{
   vFragColor = vec4(vCol, 1.0f);
}