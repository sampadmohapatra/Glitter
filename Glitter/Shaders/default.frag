#version 400 core

in vec3 vCol;
in vec3 vCircleCol;
in vec2 vTexCoord;

out vec4 vFragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixFactor;
uniform bool bDrawCircle;

void main()
{
//    vFragColor = mix(texture(texture1, vTexCoord),
//                     texture(texture2, vTexCoord), mixFactor);
    if(!bDrawCircle)
        vFragColor = texture(texture1, vTexCoord);
    else
        vFragColor = vec4(vCircleCol, 1.0);
}