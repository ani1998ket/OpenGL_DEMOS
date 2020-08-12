#version 330 core

in vec2 tex;
out vec4 color;

uniform sampler2D m_texture1;
uniform sampler2D m_texture2;

void main(){
    color = mix(texture( m_texture1, tex ) , texture( m_texture2,  vec2(1, 1) * tex ), 0.3 );
    // color = tex;
}