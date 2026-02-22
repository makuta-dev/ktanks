#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 uv;

uniform mat4 proj;
uniform mat4 view;

out vec2 f_uv;

void main(){
    gl_Position = proj * view * vec4(pos,0.0,1.0);
    f_uv = uv;
}