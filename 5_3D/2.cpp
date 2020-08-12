#include "Window.hpp"
#include "GL_Objects.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

#define printMat4( mat ) for( int i = 0; i < 4; i++ ){ for( int j = 0; j < 4; j++ ){std::cout << (mat[i][j]) << " ";}std::cout << std::endl;}
#define printVec4( vec ) for( int i = 0; i < 4; i++ ) std::cout << (vec[i]) << " "; std::cout << std::endl;
GLuint getCylinder();

int main(){
    Window window( 1280, 960, "Cylinder");

    GLuint cube_vao = getCylinder();

    glEnable( GL_DEPTH_TEST );

    Shader VertexShader( GL_VERTEX_SHADER, "shaders/1.vs");
    Shader FragmentShader( GL_FRAGMENT_SHADER, "shaders/1.fs" );
    Program program( VertexShader, FragmentShader );
    program.use();

    float t = 0.0;
    glm::vec3 eye( 0.0f, 2.0f, -3.0f );
    glm::mat4 model(1.0f), view(1.0f), projection(1.0f);
    glm::mat4 mvp(1.0f);

    glm::vec3 rotation(0.0f, 0.0f, 0.0f);

    GLuint model_loc = glGetUniformLocation( program.index, "model");
    GLuint mvp_loc = glGetUniformLocation( program.index, "mvp");
    glBindVertexArray( cube_vao ); 

    while( window.isRunning() ){
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rotation.y = t;

        model = glm::rotate( glm::mat4(1.0f), rotation.y, glm::vec3( 1.0f, 1.0f, 0.0f));
        view = glm::lookAt(eye, glm::vec3(0.0f), glm::vec3( 0.0f, 1.0f, 0.0f));
        projection = glm::perspective( 45.0f, 640.0f / 480, 0.1f, 100.0f);
        mvp = projection  * view * model; 
        glUniformMatrix4fv( mvp_loc, 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv( model_loc, 1, GL_FALSE, &model[0][0]);
        
        glDrawArrays( GL_LINE_STRIP, 0, 1024);
        window.update();
        t += 0.01;

    }
    return 0;
}

GLuint getCylinder(){
    
    const float PI = glm::pi<float>();

    const int quads = 40;
    const int vertex_count = quads * 6 * 2;
    const int vertex_size = 6;
    struct Mesh{
        int index = 0;
        float vertices[ vertex_count * vertex_size ];
    } Mesh;

    for( int i = 0; i < quads; i++ ){

        float angle_diff = ( 2 * PI / quads);

        float angle = i * angle_diff;
        float nangle = (i + 1) * angle_diff;

        float points[] = {
            glm::cos(angle),  -1.0, glm::sin(angle), glm::cos(angle), 0.0, glm::sin(angle),
            glm::cos(nangle), -1.0, glm::sin(nangle), glm::cos(nangle), 0.0, glm::sin(nangle),
            glm::cos(nangle), 1.0, glm::sin(nangle), glm::cos(nangle), 0.0, glm::sin(nangle),
            glm::cos(angle),  1.0, glm::sin(angle), glm::cos(angle), 0.0, glm::sin(angle),
            0.0,  1.0, 0.0, 0.0,  1.0, 0.0,
            0.0, -1.0, 0.0, 0.0, -1.0, 0.0
        };


        int indices[] = {
            0, 1, 2, 0, 2, 3,
            0, 1, 5,
            2, 3, 4
        };

        for( int k = 0; k < 12; k++ ){
            int v = 6 * indices[k];
            for( int j = 0; j < 6; j++ ){
                Mesh.vertices[ Mesh.index ] = points[ v + j ];
                Mesh.index++;
            }
        }
    }

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo );

    glBindVertexArray( vao );
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( Mesh.vertices ), Mesh.vertices, GL_STATIC_DRAW );
 
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof( float )) );
    glBindVertexArray( 0 );

    return vao;
}