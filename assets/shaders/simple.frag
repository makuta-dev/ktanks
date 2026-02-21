#version 330 core
in vec2 f_uv;

uniform sampler2D image;
uniform vec3 text_col;
uniform bool is_text;

out vec4 out_color;

void main(){
    if (is_text){
        float distance = texture(image, f_uv).r;
        float alpha = smoothstep(0.5 - 0.05, 0.5 + 0.05, distance);
        out_color = vec4(text_col, alpha);
    } else {
        out_color = texture(image, f_uv);
    }
}
