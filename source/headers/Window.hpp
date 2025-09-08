
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

struct WindowConfiguration {
  const char *title;
  glm::i16vec2 size;
  bool isFullscreen;
};

class Window {
    protected:
        GLFWwindow *window = nullptr;
        void configureOpenGL();
        WindowConfiguration getWindowConfiguration();

    public:
        void onInitialize();
        GLFWwindow *getWindow() { return window; }
        glm::ivec2 getFrameBufferSize() {
            glm::ivec2 size;
            glfwGetFramebufferSize(window, &(size.x), &(size.y));
            return size;
        }
        glm::ivec2 getWindowSize() {
            glm::ivec2 size;
            glfwGetWindowSize(window, &(size.x), &(size.y));
            return size;
        }
        int run();
        void onDraw(double deltaTime);
};
