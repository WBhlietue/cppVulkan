#version 450
#extension GL_ARB_separate_shader_objects : enable

// 从顶点着色器接收 materialIndex，使用 location = 0
layout(location = 0) in flat uint fragMaterialIndex; // 确保 location 匹配顶点着色器的输出

// 输出到帧缓冲，类型必须是 uint
layout(location = 0) out uint outObjectId; // 输出类型改为 uint

void main() {
    outObjectId = fragMaterialIndex+1; // 直接将 materialIndex 作为 ID 输出
}