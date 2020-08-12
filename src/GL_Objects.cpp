#include <GL/glew.h>
#include "GL_Objects.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_id);
}
VertexBuffer::VertexBuffer(void* data, int size, GLenum target, GLenum usage){
    glGenBuffers(1, &m_id);
    m_target = target;
    this->bind();
    glBufferData( target, size, data, usage);
    this->unbind();
}
VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &m_id);
}
void VertexBuffer::bind(){
    glBindBuffer( m_target, m_id );
}
void VertexBuffer::unbind(){
    glBindBuffer( m_target, 0 );
}
GLuint VertexBuffer::id(){
    return m_id;
}


VertexArray::VertexArray(){
    glGenVertexArrays( 1, &m_id );
}
VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &m_id );
}
void VertexArray::bind(){
    glBindVertexArray( m_id );
}
void VertexArray::unbind(){
    glBindVertexArray( 0 );
}

GLuint VertexArray::id(){
    return m_id;
}


Shader::Shader( GLenum type, const char* path ){
    index = glCreateShader(type);

    std::ifstream source(path);
    std::stringstream ss;

    std::string s;
    if (source) {
        ss << source.rdbuf();
        source.close();
    }
    s = ss.str();

    const char* x = s.c_str();
    glShaderSource(index, 1, &x, NULL);
    glCompileShader(index);

    char log[500];
    int length;
    glGetShaderInfoLog( index, 500, &length, log);
    std::cerr << log;
}

Program::Program( Shader vshader, Shader fshader){
    index = glCreateProgram();
    glAttachShader( index, vshader.index );
    glAttachShader( index, fshader.index );
    glLinkProgram( index );

    glValidateProgram( index );

    GLint error;
    glGetProgramiv(index, GL_VALIDATE_STATUS, &error);
    if( error == GL_FALSE){
        std::cerr << "Program Invalidated" << std::endl;
    }

    char log[500];
    int length;
    glGetProgramInfoLog( index, 500, &length, log);
    std::cerr << log;
}

void Program::use(){
    glUseProgram( index);
}
  