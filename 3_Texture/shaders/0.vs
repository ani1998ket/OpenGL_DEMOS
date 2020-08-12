#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTex;

out vec2 tex;

void main(){
    gl_Position = vPosition;
    tex = vTex;
}