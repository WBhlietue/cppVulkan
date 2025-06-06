#version 450

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inUV;  
layout(location = 3) in uint inMaterialIndex; 

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragUV;
layout(location = 2) out flat uint materialIndex;

void main() {
    gl_Position = vec4(inPos, 0.0, 1.0);
    fragColor = inColor;
    fragUV = inUV;
    materialIndex = inMaterialIndex;
}