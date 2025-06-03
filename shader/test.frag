#version 450

layout(location = 1) in vec2 fragUV;  
layout(location = 0) in vec3 fragColor;
layout(location = 2) in flat uint materialIndex;
layout(location = 0) out vec4 outColor;


struct MaterialUBO {
    vec4 color;
    vec2 pos;
    vec2 size;
    float borderRadius;
};

layout(set = 0, binding = 0) buffer Materials {
    MaterialUBO materials[];
};


void main() {
    float screenWidth = 800.0;
    float screenHeight = 600.0;
    float width = materials[materialIndex].size.x;
    float height = materials[materialIndex].size.y;
    float centerX = materials[materialIndex].pos.x;
    float centerY = materials[materialIndex].pos.y;
    float radius = materials[materialIndex].borderRadius;
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
        outColor = vec4(materials[materialIndex].color.rgb, smoothstep(0.0, fwidth(dis-radius), radius-dis) * materials[materialIndex].color.a);
    }else
    if((x < -0.5+radiusX) && (y > 0.5-radiusY)){
        vec2 pos = vec2(gl_FragCoord.x,gl_FragCoord.y);
        vec2 center = vec2((-0.5+radiusX)*width+centerX, (0.5-radiusY)*height+centerY);
        float dis = length(pos - center);
        outColor = vec4(materials[materialIndex].color.rgb, smoothstep(0.0, fwidth(dis-radius), radius-dis) * materials[materialIndex].color.a);
    }else
    if((x > 0.5-radiusX) && (y < -0.5+radiusY)){
        vec2 pos = vec2(gl_FragCoord.x,gl_FragCoord.y);
        vec2 center = vec2((0.5-radiusX)*width+centerX, (-0.5+radiusY)*height+centerY);
        float dis = length(pos - center);
        outColor = vec4(materials[materialIndex].color.rgb, smoothstep(0.0, fwidth(dis-radius), radius-dis) * materials[materialIndex].color.a);
    }else
    if((x > 0.5-radiusX) && (y > 0.5-radiusY)){
        vec2 pos = vec2(gl_FragCoord.x,gl_FragCoord.y);
        vec2 center = vec2((0.5-radiusX)*width+centerX, (0.5-radiusY)*height+centerY);
        float dis = length(pos - center);
        outColor = vec4(materials[materialIndex].color.rgb, smoothstep(0.0, fwidth(dis-radius), radius-dis) * materials[materialIndex].color.a);
    }
    
    else{
        outColor = materials[materialIndex].color;
    }
    
}

