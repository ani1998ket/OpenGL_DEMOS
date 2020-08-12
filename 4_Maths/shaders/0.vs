#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vColor;

out vec3 color;

uniform mat4 mvp;

void main(){
    gl_Position = mvp * vPosition;
    color = vColor;
}