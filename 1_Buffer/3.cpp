// Element Array

#include "Window.hpp"
#include "utils.hpp"



static GLenum DRAW_MODE = GL_LINES;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void printinfo( GLuint vao);

int main(){
    Window window(640, 480, "1");
    glfwSetKeyCallback( window.getContext(), key_callback );

    float position1[] = {
         0.5f,  0.0f,
         0.0f,  0.5f,
        -0.5f,  0.0f,
         0.0f, -0.5f
    };
    //Anti Clockwise winding
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint VAO[1];
    glGenVertexArrays(1, VAO);
    GLuint VBO[1];
    glGenBuffers(1, VBO );
    GLuint IBO[1];
    glGenBuffers(1, IBO);
    {
        {
            glBindVertexArray(VAO[0]);
            
            glBindBuffer( GL_ARRAY_BUFFER, VBO[0] );
            glBufferData( GL_ARRAY_BUFFER, sizeof(position1), position1, GL_STATIC_DRAW);
            
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO[0]);
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

            glBindVertexArray(0);
        }
    }
   
    std::cout << "Press space to Switch Modes" << std::endl;
    glClearColor(0.1, 0.1, 0.1, 1.0);

    // Element Array Buffer binding is stored in VAOs.
    printinfo(0);
    printinfo(VAO[0]);

    while( window.isRunning() ){
        glClear( GL_COLOR_BUFFER_BIT);

        
        glBindVertexArray(VAO[0]);
        glDrawElements( DRAW_MODE, 6, GL_UNSIGNED_INT, 0);

        window.update();
    }
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static int index = 0;
    GLenum DRAW_MODES[] = {
        GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP,
        GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN,
        GL_POINTS
    };
    int size = sizeof( DRAW_MODES ) / sizeof(DRAW_MODES[0]);

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        index = ( index + 1 ) % size;
        DRAW_MODE = DRAW_MODES[index];
    }
}

void printinfo( GLuint vao){
    GLint params[1];

    std::cout << "---------\n";
    glBindVertexArray( vao );
    std::cout << "VAO Bound: " << vao << std::endl;
    glGetIntegerv( GL_ELEMENT_ARRAY_BUFFER_BINDING, params);
    std::cout << "ELEMENT BUFFER: " << params[0] << std::endl;
    glGetBufferParameteriv( GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, params );
    std::cout << "SIZE: " << params[0] << std::endl;
    std::cout << "---------\n";
}