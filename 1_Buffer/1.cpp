// Multiple Objects usinng VBO

#include "Window.hpp"
#include "utils.hpp"

static GLenum DRAW_MODE = GL_LINES;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(){
    Window window(640, 480, "1");
    glfwSetKeyCallback( window.getContext(), key_callback );

    float position[] = {
        0.0f, 0.0f
    };
    float positions[] = {
         0.5f,  0.0f,
         0.0f,  0.5f,
        -0.5f,  0.0f,
         0.0f, -0.5f
    };

    GLuint VBO[2];
    glGenBuffers(2, VBO );
    {
        glBindBuffer( GL_ARRAY_BUFFER, VBO[0] );
        glBufferData( GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

        glBindBuffer( GL_ARRAY_BUFFER, VBO[1] );
        glBufferData( GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    }
   
    std::cout << "Press space to Switch Modes" << std::endl;
    glClearColor(0.1, 0.1, 0.1, 1.0);

    while( window.isRunning() ){
        glClear( GL_COLOR_BUFFER_BIT);
        {
            glBindBuffer( GL_ARRAY_BUFFER,  VBO[0]);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glDrawArrays( GL_POINTS, 0, 1);
        }
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glDrawArrays( DRAW_MODE, 0, 4);
            window.update();
        }
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