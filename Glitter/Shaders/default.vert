#version 400 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

out vec3 vFragNormal;
out vec3 vFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalMatrix;

void main() {
    gl_Position = projection * view * model * vec4(vPos, 1.0f);

    // notice conversion from vec4 to vec3. 'w' is dropped
    vFragPos = vec3(model * vec4(vPos, 1.0f));
//    vFragNormal = mat3(transpose(inverse(model))) * vNormal;
    vFragNormal = mat3(normalMatrix) * vNormal;
}