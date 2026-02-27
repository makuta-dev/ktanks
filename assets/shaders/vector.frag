#version 460 core

layout (location = 0) in vec2 vUV;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec2 vSize;
layout (location = 3) in float vThickness;
layout (location = 4) in float vRadius;
layout (location = 5) in flat int vType;

out vec4 FragColor;

void main() {
    float dist = 0.0;
    vec2 pixelPos = vUV * (vSize * 0.5);

    if (vType == 0) {
        vec2 d = abs(pixelPos) - (vSize * 0.5);
        dist = length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);
    } else if (vType == 1) {
        vec2 r = vSize * 0.5;

        float k0 = length(pixelPos / r);
        float k1 = length(pixelPos / (r * r));

        dist = k0 * (k0 - 1.0) / k1;
    } else if (vType == 2) {
        vec2 q = abs(pixelPos) - (vSize * 0.5) + vRadius;
        dist = length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - vRadius;
    }

    float edgeSoftness = fwidth(dist);
    float alpha = 0.0;

    if (vThickness <= 0.0) {
        alpha = 1.0 - smoothstep(-edgeSoftness, edgeSoftness, dist);
    } else {
        float outer = 1.0 - smoothstep(-edgeSoftness, edgeSoftness, dist);
        float inner = 1.0 - smoothstep(-edgeSoftness, edgeSoftness, dist + vThickness);
        alpha = clamp(outer - inner, 0.0, 1.0);
    }

    if (alpha <= 0.001) discard;
    FragColor = vec4(vColor.rgb, vColor.a * alpha);
}