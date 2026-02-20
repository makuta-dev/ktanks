#version 330 core
in vec2 f_uv;

uniform sampler2D image;

out vec4 out_color;

void main(){
    vec4 texColor = texture(image,f_uv);

    if(texColor.a < 0.1)
        discard;

    out_color = texColor;
}
