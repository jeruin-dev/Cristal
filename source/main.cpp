#include <Window.hpp>
#include <GLFW/glfw3.h>
#include <fmt/base.h>

void glfw_error_callback(int error, const char* description){
    fmt::println("GLFW Error: {} : {}", error, description);
}

class Cristal : Window{
    public:
    int run() {
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
        while(!glfwWindowShouldClose(window)){
            glfwPollEvents();

            auto frame_buffer_size = getFrameBufferSize();
            glViewport(0, 0, frame_buffer_size.x, frame_buffer_size.y);


            double current_frame_time = glfwGetTime();
            onDraw(current_frame_time - last_frame_time);
            last_frame_time = current_frame_time;

            glfwSwapBuffers(window);
        }

        glfwDestroyWindow(window);

        glfwTerminate();
        return 0;
  }
};


int main(){

    auto cristal = new Cristal;

    cristal->run();

    return 0;
}
