#include <GLFW/glfw3.h>

int main(){
    if( glfwInit() == GL_FALSE ){
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow( 640, 480, "0", nullptr, nullptr);

    if( !window ){
        glfwTerminate();
        return -1;
    }

    while( !glfwWindowShouldClose(window) ){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}