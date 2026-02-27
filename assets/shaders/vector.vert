#version 460 core

layout (location = 0) in vec2 aCorner;
layout (location = 1) in vec2 aPos;
layout (location = 2) in vec2 aSize;
layout (location = 3) in vec4 aColor;
layout (location = 4) in float aThickness;
layout (location = 5) in float aRadius;
layout (location = 6) in int aType;

layout (location = 0) out vec2 vUV;
layout (location = 1) out vec4 vColor;
layout (location = 2) out vec2 vSize;
layout (location = 3) out float vThickness;
layout (location = 4) out float vRadius;
layout (location = 5) out flat int vType;

uniform mat4 u_projection;

void main() {
    vUV = aCorner * 2.0 - 1.0;
    vColor = aColor;
    vSize = aSize;
    vThickness = aThickness;
    vRadius = aRadius;
    vType = aType;

    vec2 worldPos = aPos + (aCorner * aSize);
    gl_Position = u_projection * vec4(worldPos, 0.0, 1.0);
}