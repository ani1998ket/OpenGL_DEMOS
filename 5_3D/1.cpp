#include "Window.hpp"
#include "GL_Objects.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

#define printMat4( mat ) for( int i = 0; i < 4; i++ ){ for( int j = 0; j < 4; j++ ){std::cout << (mat[i][j]) << " ";}std::cout << std::endl;}
#define printVec4( vec ) for( int i = 0; i < 4; i++ ) std::cout << (vec[i]) << " "; std::cout << std::endl;
GLuint getCube();

int main(){
    Window window( 640, 480, "Cube");

    GLuint cube_vao = getCube();

    glEnable( GL_DEPTH_TEST );

    Shader VertexShader( GL_VERTEX_SHADER, "shaders/1.vs");
    Shader FragmentShader( GL_FRAGMENT_SHADER, "shaders/1.fs" );
    Program program( VertexShader, FragmentShader );
    program.use();

    float t = 0.0;
    glm::vec3 eye( 0.0f, 1.0f, -3.0f );
    glm::mat4 model(1.0f), view(1.0f), projection(1.0f);
    glm::mat4 mvp(1.0f);

    glm::vec3 rotation(0.0f, 0.0f, 0.0f);

    GLuint model_loc = glGetUniformLocation( program.index, "model");
    GLuint mvp_loc = glGetUniformLocation( program.index, "mvp");
    glBindVertexArray( cube_vao ); 

    while( window.isRunning() ){
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rotation.y = t;

        model = glm::rotate( glm::mat4(1.0f), rotation.y, glm::vec3( 0.0f, 1.0f, 0.0f));
        view = glm::lookAt(eye, glm::vec3(0.0f), glm::vec3( 0.0f, 1.0f, 0.0f));
        projection = glm::perspective( 45.0f, 640.0f / 480, 0.1f, 100.0f);
        mvp = projection  * view * model; 
        glUniformMatrix4fv( mvp_loc, 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv( model_loc, 1, GL_FALSE, &model[0][0]);
        
        glDrawArrays( GL_TRIANGLES, 0, 36);
        window.update();
        t += 0.01;

    }
    return 0;
}

GLuint getCube(){
    
    struct Cube{
        float positions[24];
        float normals[24];
        unsigned int indices[ 36 ];
    };

    // Code to generate vertices
    // Cube cube{
    //     {
    //         -0.5, -0.5, -0.5, //0
    //          0.5, -0.5, -0.5, //1
    //          0.5,  0.5, -0.5, //2
    //         -0.5,  0.5, -0.5, //3

    //         -0.5, -0.5,  0.5, //4
    //          0.5, -0.5,  0.5, //5
    //          0.5,  0.5,  0.5, //6
    //         -0.5,  0.5,  0.5  //7
    //     },
    //     {
    //         0.0, 0.0, -1.0f, // -Z
    //         0.0, 0.0,  1.0f, // Z
            
    //         -1.0, 0.0,  0.0f, // -X
    //          1.0, 0.0,  0.0f, // X
            
    //         0.0, -1.0,  0.0f, // -Y
    //         0.0,  1.0,  0.0f, // Y
    //     },
    //     {
    //         0, 1, 2, 0, 2, 3, //front
    //         5, 4, 7, 5, 7, 6, //back

    //         4, 0, 3, 4, 3, 7,//left
    //         1, 5, 6, 1, 6, 2, //right

    //         4, 5, 1, 4, 1, 0, //down
    //         3, 2, 6, 3, 6, 7 //up
    //     }
    // };

    // for( int n = 0; n < 6; n++){
    //     for( int j = 0; j < 6; j++){
    //         int index = cube.indices[ 6 * n + j ];
    //         for( int i = 0; i < 3; i++){
    //             std::cout << cube.positions[index * 3 + i] << ", ";
    //         }
    //         for( int i = 0; i < 3; i++){
    //             std::cout << cube.normals[n * 3 + i] << ", ";
    //         }
    //         std::cout << std::endl;
    //     }
    // }

    float vertices[] = {
        -0.5, -0.5, -0.5, 0, 0, -1, 
        0.5, -0.5, -0.5, 0, 0, -1, 
        0.5, 0.5, -0.5, 0, 0, -1, 
        -0.5, -0.5, -0.5, 0, 0, -1, 
        0.5, 0.5, -0.5, 0, 0, -1, 
        -0.5, 0.5, -0.5, 0, 0, -1, 
        0.5, -0.5, 0.5, 0, 0, 1, 
        -0.5, -0.5, 0.5, 0, 0, 1, 
        -0.5, 0.5, 0.5, 0, 0, 1, 
        0.5, -0.5, 0.5, 0, 0, 1, 
        -0.5, 0.5, 0.5, 0, 0, 1, 
        0.5, 0.5, 0.5, 0, 0, 1, 
        -0.5, -0.5, 0.5, -1, 0, 0, 
        -0.5, -0.5, -0.5, -1, 0, 0, 
        -0.5, 0.5, -0.5, -1, 0, 0, 
        -0.5, -0.5, 0.5, -1, 0, 0, 
        -0.5, 0.5, -0.5, -1, 0, 0, 
        -0.5, 0.5, 0.5, -1, 0, 0, 
        0.5, -0.5, -0.5, 1, 0, 0, 
        0.5, -0.5, 0.5, 1, 0, 0, 
        0.5, 0.5, 0.5, 1, 0, 0, 
        0.5, -0.5, -0.5, 1, 0, 0, 
        0.5, 0.5, 0.5, 1, 0, 0, 
        0.5, 0.5, -0.5, 1, 0, 0, 
        -0.5, -0.5, 0.5, 0, -1, 0, 
        0.5, -0.5, 0.5, 0, -1, 0, 
        0.5, -0.5, -0.5, 0, -1, 0, 
        -0.5, -0.5, 0.5, 0, -1, 0, 
        0.5, -0.5, -0.5, 0, -1, 0, 
        -0.5, -0.5, -0.5, 0, -1, 0, 
        -0.5, 0.5, -0.5, 0, 1, 0, 
        0.5, 0.5, -0.5, 0, 1, 0, 
        0.5, 0.5, 0.5, 0, 1, 0, 
        -0.5, 0.5, -0.5, 0, 1, 0, 
        0.5, 0.5, 0.5, 0, 1, 0, 
        -0.5, 0.5, 0.5, 0, 1, 0
    };


    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo );

    glBindVertexArray( vao );
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
 
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof( float )) );
    glBindVertexArray( 0 );

    return vao;
}