// VAO : Vertex Array Object

#include "Window.hpp"
#include "utils.hpp"

static GLenum DRAW_MODE = GL_LINES;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void printinfo( GLuint vao);

int main(){
    Window window(640, 480, "1");
    glfwSetKeyCallback( window.getContext(), key_callback );

    float position1[] = {
        0.7f, 0.7f,
        0.8f, 0.6f
    };
    float position2[] = {
         0.5f,  0.0f,
         0.0f,  0.5f,
        -0.5f,  0.0f,
         0.0f, -0.5f
    };

    GLuint VAO[2];
    glGenVertexArrays(2, VAO);
    GLuint VBO[2];
    glGenBuffers(2, VBO );
    {
        {
            glBindVertexArray(VAO[0]);
            glBindBuffer( GL_ARRAY_BUFFER, VBO[0] );
            glBufferData( GL_ARRAY_BUFFER, sizeof(position1), position1, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

            glBindVertexArray(0);
        }
        {  
            glBindVertexArray(VAO[1]);
            glBindBuffer( GL_ARRAY_BUFFER, VBO[1] );
            glBufferData( GL_ARRAY_BUFFER, sizeof(position2), position2, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

            glBindVertexArray(0);
        }
    }
   
    std::cout << "Press space to Switch Modes" << std::endl;
    glClearColor(0.1, 0.1, 0.1, 1.0);
    
    // Array Buffer binding is not stored in VAOs.
    printinfo(VAO[0]);
    printinfo(VAO[1]);
    while( window.isRunning() ){
        glClear( GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO[0]);
        glDrawArrays( GL_LINES, 0, 2);

        glBindVertexArray(VAO[1]);
        glDrawArrays( DRAW_MODE, 0, 4);

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
    glGetIntegerv( GL_ARRAY_BUFFER_BINDING, params);
    std::cout << "Array BUFFER: " << params[0] << std::endl;
    glGetBufferParameteriv( GL_ARRAY_BUFFER, GL_BUFFER_SIZE, params );
    std::cout << "SIZE: " << params[0] << std::endl;
    std::cout << "---------\n";
}