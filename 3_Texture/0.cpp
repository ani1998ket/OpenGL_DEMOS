#include <iostream>
#include <string>

#include "Window.hpp"
#include "GL_Objects.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Image{

    unsigned char* data;
    const char* path;
    int width, height, channels;

    Image( std::string path){
        this->path = path.c_str();
        data = stbi_load( this->path, &width, &height, &channels, STBI_rgb_alpha);
         if( data == NULL ){
        std::cerr << "Error" << std::endl;
        }else{
            std::cout << "Image Loaded with: ";
            std::cout << width << "," << height << "," << channels << std::endl;
        }
    }

    ~Image(){   
        stbi_image_free( data );
    }
};

int main(){

    Window window( 640, 480, "0");
    stbi_set_flip_vertically_on_load(1);

    Shader vshader( GL_VERTEX_SHADER, "shaders/0.vs");
    Shader fshader( GL_FRAGMENT_SHADER, "shaders/0.fs");
    Program program( vshader, fshader );
    program.use();

    float positions[] = {
        -0.8, -0.8,
         0.8, -0.8,
         0.8,  0.8,
        -0.8,  0.8
    };
    float texels[] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    VertexArray VAO;
    VertexBuffer VBO_pos(positions, sizeof( positions), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    VertexBuffer VBO_tex(texels, sizeof( texels), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    VertexBuffer IBO(indices, sizeof( indices), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    VAO.bind();
    VBO_pos.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    VBO_tex.bind();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    IBO.bind();
    VAO.unbind();

    Image wall_image( "res/wall.png");
    Image brick_image("res/bricks.jpg");

    GLuint textures[2];
    {
        glGenTextures(2, textures);

        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, textures[0] );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, wall_image.width, wall_image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, wall_image.data );
        glGenerateMipmap(GL_TEXTURE_2D);

        glActiveTexture( GL_TEXTURE1 );
        glBindTexture( GL_TEXTURE_2D, textures[1] );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, brick_image.width, brick_image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, brick_image.data );
        glGenerateMipmap(GL_TEXTURE_2D);

        glUniform1i( glGetUniformLocation(program.index, "m_texture1"), 0);
        glUniform1i( glGetUniformLocation(program.index, "m_texture2"), 1);
        
    }

    glClearColor( 0.5, 0.5, 0.5, 1.0);
    while( window.isRunning() ){
        glClear( GL_COLOR_BUFFER_BIT );
        VAO.bind();
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        window.update();
    }
    return 0;
}
