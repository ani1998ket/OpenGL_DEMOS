#include "Window.hpp"

int main(){
    Window window(640, 480, "1");

    while( window.isRunning() ){
        window.update();
    }
    return 0;
}
