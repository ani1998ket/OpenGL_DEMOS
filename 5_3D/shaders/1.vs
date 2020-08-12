#version 330 core

layout(location = 0) in vec4 v_position;
layout(location = 1) in vec4 v_normal;

uniform mat4 model;
uniform mat4 mvp;
out vec4 color;
vec4 normal;

void main(){
    gl_Position =  mvp * v_position;
    normal = model * v_normal;
    float intensity = max( 0, dot( vec3(0.0f, 1.0f, -2.0f) , normal.xyz ) ); 
    color = vec4( 0.5, 0.5, 0.5, 1.0) * vec4( vec3( intensity ), 1.0);
}