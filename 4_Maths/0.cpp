#include <iostream>
#include <string>

#include "Window.hpp"
#include "GL_Objects.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <cmath>

int main(){

    Window window( 640, 480, "0");

    Shader vshader( GL_VERTEX_SHADER, "shaders/0.vs");
    Shader fshader( GL_FRAGMENT_SHADER, "shaders/0.fs");
    Program program( vshader, fshader );
    program.use();

    float positions[] = {
        -0.5, -0.5, 0.0,
         0.5, -0.5, 0.0,
         0.5,  0.5, 0.0,
        -0.5,  0.5, 0.0
    };
    float colors[] = {
        1.0, 0.0, 0.0,
        1.0, 0.0, 1.0,
        0.0, 1.0, 0.0,
        1.0, 1.0, 1.0
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    VertexArray VAO;
    VertexBuffer VBO_pos(positions, sizeof( positions), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    VertexBuffer VBO_col(colors, sizeof( colors), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    VertexBuffer IBO(indices, sizeof( indices), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    GLuint model_loc = glGetUniformLocation( program.index, "mvp");
    glm::mat4 model(1.0f), view(1.0f), projection(1.0f);

    VAO.bind();
    VBO_pos.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    VBO_col.bind();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    IBO.bind();
    VAO.unbind();

    glClearColor( 0.5, 0.5, 0.5, 1.0);
    float t = 0;
    while( window.isRunning() ){
        glClear( GL_COLOR_BUFFER_BIT );

        VAO.bind();

        model = glm::mat4(1.0);
        // model = glm::translate( glm::mat4(1.0), glm::vec3( sin(t) / 2, cos(t) / 2, 0.0) );
        // model = glm::scale( model, glm::vec3( sin(t) + 1, sin(t) + 1, 1.0) );
        // model = glm::rotate( model, 2 * float(sin(t) * 3.14), glm::vec3(0.0f, 0.0f, 1.0f) );
        model = glm::translate( glm::mat4(1.0), glm::vec3( 0, 0, sin(t)) );
        model = glm::rotate( model, float(sin(t) * 3.14), glm::vec3(0.0f, 0.0f, 1.0f) );


        glm::vec3 eye( 4 *cos(t / 4), 0.0, 4 *sin(t / 4) );
        view = glm::lookAt( eye, glm::vec3(0.0, 0.0, 0.0), glm::vec3( 0.0, 1.0, 0.0));
        
        projection = glm::perspective( 45.0f , 640.0f/ 480, 0.1f, 100.0f);
        // projection = glm::ortho( -1.0f, 1.0f, -1.0f, 1.0f);

        glm::mat4 mvp = projection * view * model;
        glUniformMatrix4fv( model_loc, 1, GL_FALSE,  &mvp[0][0]);
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.update();
        t += 0.05;
    }
    return 0;
}
