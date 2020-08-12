#include "GLFW/glfw3.h"

class VertexBuffer{

    GLuint m_id;
    GLenum m_target;

    public:
    VertexBuffer();
    VertexBuffer(void* data, int size, GLenum target, GLenum usage);
    ~VertexBuffer();

    void bind();
    void unbind();
    void fillData();
    GLuint id();

};

class VertexArray{
    GLuint m_id;

    public:
    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();
    GLuint id();
};

class Shader{
    public:
    GLuint index;
    Shader() = delete;
    Shader(GLenum type, const char* path);
};

class Program{
    public:
    GLuint index;
    Program() = delete;
    Program( Shader vertex, Shader fragment);

    void use();
};

