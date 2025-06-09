#version 450

layout(location = 0) in vec2 fragUV;  
layout(location = 0) out vec4 outColor;


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
    // outColor = vec4(1.0,1.0,0.0,1.0);
    float screenWidth =pc.screen_width;
    float screenHeight = pc.screen_height;
    float width = pc.size.x;
    float height = pc.size.y;
    float centerX = pc.pos.x;
    float centerY = pc.pos.y;
    float radius = pc.borderRadius;
    float radiusX = radius / width;
    float radiusY = radius / height;



    centerX += screenWidth/2;
    centerY += screenHeight/2;
    float x = gl_FragCoord.x - centerX;
    float y = gl_FragCoord.y - centerY;

    x /= width;
    y /= height;
    
    if((x <= -0.5+radiusX) && (y <= -0.5+radiusY)){
        vec2 pos = vec2(gl_FragCoord.x,gl_FragCoord.y);
        vec2 center = vec2((-0.5+radiusX)*width+centerX, (-0.5+radiusY)*height+centerY);
        float dis = length(pos - center);
        outColor = vec4(pc.color.rgb, smoothstep(0.0, fwidth(dis-radius), radius-dis) * pc.color.a);
    }else
    if((x < -0.5+radiusX) && (y > 0.5-radiusY)){
        vec2 pos = vec2(gl_FragCoord.x,gl_FragCoord.y);
        vec2 center = vec2((-0.5+radiusX)*width+centerX, (0.5-radiusY)*height+centerY);
        float dis = length(pos - center);
        outColor = vec4(pc.color.rgb, smoothstep(0.0, fwidth(dis-radius), radius-dis) * pc.color.a);
    }else
    if((x > 0.5-radiusX) && (y < -0.5+radiusY)){
        vec2 pos = vec2(gl_FragCoord.x,gl_FragCoord.y);
        vec2 center = vec2((0.5-radiusX)*width+centerX, (-0.5+radiusY)*height+centerY);
        float dis = length(pos - center);
        outColor = vec4(pc.color.rgb, smoothstep(0.0, fwidth(dis-radius), radius-dis) * pc.color.a);
    }else
    if((x > 0.5-radiusX) && (y > 0.5-radiusY)){
        vec2 pos = vec2(gl_FragCoord.x,gl_FragCoord.y);
        vec2 center = vec2((0.5-radiusX)*width+centerX, (0.5-radiusY)*height+centerY);
        float dis = length(pos - center);
        outColor = vec4(pc.color.rgb, smoothstep(0.0, fwidth(dis-radius), radius-dis) * pc.color.a);
    }
    
    else{
        outColor = pc.color;
    }
    
}

