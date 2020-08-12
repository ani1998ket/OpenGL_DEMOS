#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window{

    GLFWwindow* window;

    public:
    int width, height;
    const char* heading;

    public:
    Window(int width = 640, int height = 480, const char* heading = "");
    ~Window();

    bool isRunning() const;   
    void makeCurrent() const; 
    GLFWwindow* getContext() const;
    void update() const;
    void swapBuffers() const;
    void pollEvents() const;
};