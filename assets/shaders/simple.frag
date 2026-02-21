#version 330 core
in vec2 f_uv;

uniform sampler2D image;

out vec4 out_color;

void main(){
    out_color = texture(image,f_uv);
}
