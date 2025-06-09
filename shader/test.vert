#version 450

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inUV;  

layout(location = 0) out vec2 fragUV;

layout(push_constant,std140) uniform PushConstants {
    vec4 color;
    vec2 size;
    vec2 pos;
    vec2 scale;
    int id;
    int screen_width;
    int screen_height;
    float rotation;
    float borderRadius;
} pc;


void main() {


    float centerX = (pc.pos.x) * 2 / pc.screen_width;
    float centerY = (pc.pos.y) * 2 / pc.screen_height;
    float x = pc.size.x / pc.screen_width;
    float y = pc.size.y / pc.screen_height;

    vec2 pos;

    if(inPos.x == -1 && inPos.y == -1){
        pos = vec2(centerX-x, centerY-y);
    }else if(inPos.x == 1 && inPos.y == -1){
        pos = vec2(centerX+x, centerY-y);
    }else if(inPos.x == -1 && inPos.y == 1){
        pos = vec2(centerX-x, centerY+y);
    }else if(inPos.x == 1 && inPos.y == 1){
        pos = vec2(centerX+x, centerY+y);
    }



    fragUV = inUV;
    gl_Position = vec4(pos, 0.0, 1.0);
}