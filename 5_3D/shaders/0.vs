#version 330 core

layout(location = 0) in vec4 v_position;
layout(location = 1) in vec3 v_normal;

uniform mat4 mvp;
// out vec4 color;

void main(){
    gl_Position =  mvp * v_position;
}