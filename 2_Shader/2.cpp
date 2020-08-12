#include <fstream>
#include <sstream>
#include <string>

#include "Window.hpp"
#include "utils.hpp"

void readFile( const char* path, std::string& destination);

int main(){
    Window window(640, 480, "1");

    float position1[] = {
         0.5f,  0.0f,
         0.0f,  0.5f,
        -0.5f,  0.0f,
         0.0f, -0.5f
    };

    float colors[] = {
        1.0, 1.0, 1.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 0.0, 0.0
    };
    //Anti Clockwise winding
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint VAO[1];
    glGenVertexArrays(1, VAO);
    GLuint VBO[2];
    glGenBuffers(2, VBO );
    GLuint IBO[1];
    glGenBuffers(1, IBO);
    {
        {
            glBindVertexArray(VAO[0]);
            
            glBindBuffer( GL_ARRAY_BUFFER, VBO[0] );
            glBufferData( GL_ARRAY_BUFFER, sizeof(position1), position1, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer( GL_ARRAY_BUFFER, VBO[1] );
            glBufferData( GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
            
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO[0]);
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glBindVertexArray(0);
        }
    }

    GLuint vshader = glCreateShader( GL_VERTEX_SHADER );
    GLuint fshader = glCreateShader( GL_FRAGMENT_SHADER );
    GLuint program = glCreateProgram();

    std::string vshaderSource;
    readFile("./shaders/2.vs", vshaderSource);
    std::string fshaderSource;
    readFile("./shaders/2.fs", fshaderSource);

    const char* vshaderSource_c = vshaderSource.c_str();
    const char* fshaderSource_c = fshaderSource.c_str();

    glShaderSource( vshader, 1, &vshaderSource_c, nullptr);
    glCompileShader(vshader);
    glShaderSource( fshader, 1, &fshaderSource_c, nullptr);
    glCompileShader( fshader );

    glAttachShader( program, vshader );
    glAttachShader( program, fshader );
    glLinkProgram( program );
    glUseProgram( program );

    glClearColor(0.1, 0.1, 0.1, 1.0);

    while( window.isRunning() ){
        glClear( GL_COLOR_BUFFER_BIT);

        
        glBindVertexArray(VAO[0]);
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.update();
    }
    return 0;
}

void readFile( const char* path, std::string& destination){
    std::ifstream source(path);
    std::stringstream ss;
    std::string s;

    if (source) {
        ss << source.rdbuf();    
        source.close();
    }
    s = ss.str();
    destination = s;
}