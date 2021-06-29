#version 400 core

in vec3 vFragPos;
in vec3 vFragNormal;

out vec4 vFragColor;

uniform vec3 vObjectColor;
uniform vec3 vLightPos;
uniform vec3 vLightColor;
uniform vec3 vViewerPos;

void main() {
    float fAmbientStrength = 0.1f;
    vec3 vAmbient = fAmbientStrength * vLightColor;

    vec3 vNormal = normalize(vFragNormal);
    vec3 vLightDir = normalize(vLightPos-vFragPos);

    float fDiffuse = max(dot(vNormal, vLightDir), 0.0f);
    vec3 vDiffuse = fDiffuse * vLightColor;

    float fSpecularStrength = 0.5f;
    vec3 vViewDir = normalize(vViewerPos - vFragPos);
    vec3 vReflectDir = reflect(-vLightDir, vNormal);

    float fSpecular = pow(max(dot(vViewDir, vReflectDir), 0.0), 32);
    vec3 vSpecular = fSpecularStrength * fSpecular * vLightColor;

    vec3 result = (vAmbient + vDiffuse + vSpecular) * vObjectColor;
    vFragColor = vec4(result, 1.0f);
}