#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aSize;
layout (location = 4) in float aThickness;
layout (location = 5) in int aType;

layout (location = 0) out vec2 vUV;
layout (location = 1) out vec4 vColor;
layout (location = 2) out vec2 vSize;
layout (location = 3) out float vThickness;
layout (location = 4) out flat int vType;

uniform mat4 u_projection;

void main() {
    vUV = aUV;
    vColor = aColor;
    vSize = aSize;
    vThickness = aThickness;
    vType = aType;
    gl_Position = u_projection * vec4(aPos, 0.0, 1.0);
}