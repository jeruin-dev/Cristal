#include "headers/Cristal.hpp"
#include <GLFW/glfw3.h>
#include <fmt/base.h>
#include "triangulo.cpp"

void glfw_error_callback(int error, const char* description){
    fmt::println("GLFW Error: {} : {}", error, description);
}

void App::Cristal::onInitialize(){
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
}

void App::Cristal::configureOpenGL(){
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

App::WindowConfiguration App::Cristal::getWindowConfiguration(){
        return {"Cristal", {800, 600}, false };
}

int App::Cristal::run(){
        glfwSetErrorCallback(glfw_error_callback);

        if(!glfwInit()){
             fmt::println("Failed to Initialize GLFW");
            return -1;
        }

        configureOpenGL();

        auto win_config = getWindowConfiguration();

        GLFWmonitor* monitor = win_config.isFullscreen ? glfwGetPrimaryMonitor() : nullptr;
        window = glfwCreateWindow(win_config.size.x, win_config.size.y, win_config.title, monitor, nullptr);
        if(!window) {
            fmt::println ("Failed to Create Window");
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
             fmt::println("Error: no se pudo inicializar GLAD\n");
            return -1;
        }

    #if defined(ENABLE_OPENGL_DEBUG_MESSAGES)
        glDebugMessageCallback(opengl_callback, nullptr);
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    #endif



        onInitialize();
        double last_frame_time = glfwGetTime();
        triangel::setup();
        while(!glfwWindowShouldClose(window)){
            glfwPollEvents();

            auto frame_buffer_size = getFrameBufferSize();
            glViewport(0, 0, frame_buffer_size.x, frame_buffer_size.y);


            double current_frame_time = glfwGetTime();
                   onDraw(current_frame_time - last_frame_time);
                   last_frame_time = current_frame_time;

            triangel::render(frame_buffer_size.x, frame_buffer_size.y);
            glfwSwapBuffers(window);
        }

        glfwDestroyWindow(window);

        glfwTerminate();
        return 0;
}

void App::Cristal::onDraw(double deltaTime){
    glClear(GL_COLOR_BUFFER_BIT);
}
