#include <GL/glew.h>
#include <iostream>
#include "Window.hpp"

#include "utils.hpp"

Window::Window(int width, int height, const char* heading) 
    : width(width), height(height), heading(heading)
{
    if( !glfwInit() ){
        printE("GLFW", "Initialisation");
        exit(-1);
    }

    // glfwWindowHint( GL_CONTEXT_)
    window = glfwCreateWindow(width, height,heading, NULL, NULL);
    if(!window){
        printE("GLFW", "Window Creation");
        glfwTerminate();
        exit(-1);
    }
    this->makeCurrent();
    glfwSwapInterval(1);
    if( glewInit() != GLEW_OK ){
        printE("GLEW", "Initialisation" );
    }
    std::cout << "Window created\n";
}
Window::~Window() {
    glfwDestroyWindow(window);
    std::cout << "Window destroyed\n";
    glfwTerminate();
}

bool Window::isRunning() const {
    return !glfwWindowShouldClose(window);
}

GLFWwindow* Window::getContext() const {
    return window;
}

void Window::makeCurrent() const {
    glfwMakeContextCurrent(window);
}

void Window::swapBuffers() const{
    glfwSwapBuffers( window );
}

void Window::pollEvents() const{
    glfwPollEvents();
}
void Window::update() const{
    swapBuffers();
    pollEvents();
}
