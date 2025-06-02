#version 450

layout(location = 1) in vec2 fragUV;  
layout(location = 0) in vec3 fragColor;
layout(location = 0) out vec4 outColor;


void main() {
    float screenWidth = 800.0;
    float screenHeight = 600.0;
    float width = 200.0;
    float height = 100.0;
    float centerX = 100;
    float centerY = 100;
    float radius = 20.0;
    float radiusX = radius / width;
    float radiusY = radius / height;



    centerX += screenWidth/2;
    centerY += screenHeight/2;
    float x = gl_FragCoord.x - centerX;
    float y = gl_FragCoord.y - centerY;

    x /= width;
    y /= height;

    // y+=1;
    if(fragColor == vec3(1.0,1.0,1.0)){
        outColor = vec4(1.0,1.0,1.0,1.0);
    }else{
        if((x <= -0.5+radiusX) && (y <= -0.5+radiusY)){
            // outColor = vec4(0.0,0.0,0.0,0.0);
            vec2 pos = vec2(gl_FragCoord.x,gl_FragCoord.y);
            vec2 center = vec2((-0.5+radiusX)*width+centerX, (-0.5+radiusY)*height+centerY);
            float dis = length(pos - center);
            // if(dis < radius){
            //     outColor = vec4(fragColor, 1.0);
            // }
            outColor = vec4(fragColor, smoothstep(0.0, fwidth(dis-radius), radius-dis));
        }else
        if((x < -0.5+radiusX) && (y > 0.5-radiusY)){
            outColor = vec4(0.0,0.0,0.0,0.0);
            vec2 pos = vec2(gl_FragCoord.x,gl_FragCoord.y);
            vec2 center = vec2((-0.5+radiusX)*width+centerX, (0.5-radiusY)*height+centerY);
            float distance = length(pos - center);
            if(distance < radius){
                outColor = vec4(fragColor, 1.0);
            }
        }else
        if((x > 0.5-radiusX) && (y < -0.5+radiusY)){
            outColor = vec4(0.0,0.0,0.0,0.0);
            vec2 pos = vec2(gl_FragCoord.x,gl_FragCoord.y);
            vec2 center = vec2((0.5-radiusX)*width+centerX, (-0.5+radiusY)*height+centerY);
            float distance = length(pos - center);
            if(distance < radius){
                outColor = vec4(fragColor, 1.0);
            }
        }else
        if((x > 0.5-radiusX) && (y > 0.5-radiusY)){
            outColor = vec4(0.0,0.0,0.0,0.0);
            vec2 pos = vec2(gl_FragCoord.x,gl_FragCoord.y);
            vec2 center = vec2((0.5-radiusX)*width+centerX, (0.5-radiusY)*height+centerY);
            float distance = length(pos - center);
            if(distance < radius){
                outColor = vec4(fragColor, 1.0);
            }
        }
        
        else{
            outColor = vec4(fragColor, 1.0);
        }
    }
}

