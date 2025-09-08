#include "headers/Window.hpp"
#include <GLFW/glfw3.h>
#include <fmt/base.h>


void Window::onInitialize(){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void Window::configureOpenGL(){
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        glfwWindowHint(GLFW_SAMPLES, 0);

        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

        glfwWindowHint(GLFW_RED_BITS, 8);
        glfwWindowHint(GLFW_GREEN_BITS, 8);
        glfwWindowHint(GLFW_BLUE_BITS, 8);
        glfwWindowHint(GLFW_ALPHA_BITS, 8);

        glfwWindowHint(GLFW_DEPTH_BITS, 24);

        glfwWindowHint(GLFW_STENCIL_BITS, 8);

        glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
}

WindowConfiguration Window::getWindowConfiguration(){
        return {"Window", {800, 600}, false };
}

void Window::onDraw(double deltaTime){
    glClear(GL_COLOR_BUFFER_BIT);
}
