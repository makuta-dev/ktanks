#version 460 core

layout (location = 0) in vec2 vUV;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec2 vSize;
layout (location = 3) in float vThickness;
layout (location = 4) in flat int vType;

out vec4 FragColor;

void main() {
    float dist = 0.0;

    if (vType == 0) {
        vec2 d = abs(vUV) - vec4(1.0).xy;
        dist = length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);
    } else {
        dist = length(vUV) - 1.0;
    }

    float pixelDist = dist * (min(vSize.x, vSize.y) * 0.5);

    float edgeSoftness = fwidth(pixelDist);
    if (edgeSoftness < 0.001) edgeSoftness = 0.707;

    float alpha = 0.0;
    if (vThickness <= 0.0) {
        alpha = 1.0 - smoothstep(-edgeSoftness, edgeSoftness, pixelDist);
    } else {
        float outer = 1.0 - smoothstep(-edgeSoftness, edgeSoftness, pixelDist);
        float inner = 1.0 - smoothstep(-edgeSoftness, edgeSoftness, pixelDist + vThickness);
        alpha = clamp(outer - inner, 0.0, 1.0);
    }

    if (alpha <= 0.0) discard;
    FragColor = vec4(vColor.rgb, vColor.a * alpha);
}