#version 450

layout(location = 1) in vec2 fragUV;  
layout(location = 0) in vec3 fragColor;
layout(location = 0) out vec4 outColor;


void main() {


    float screenHeight = 600.0;
    float aloha = gl_FragCoord.y / screenHeight;
    vec2 uv = fragUV;
    outColor = vec4(fragColor, 1.0);
}

