#include <Window.hpp>
#include <GLFW/glfw3.h>
#include <fmt/base.h>
#include <Render.hpp>
void glfw_error_callback(int error, const char* description){
    fmt::println("GLFW Error: {} : {}", error, description);
}



int main(){



    return 0;
}
