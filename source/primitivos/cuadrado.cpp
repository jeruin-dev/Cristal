#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/base.h>
namespace MP {
    const char *vertexShaderSource = R"(
        #version 330 core

        layout (location = 0) in vec3 apos;   // posición del vértice
        layout (location = 1) in vec3 acolor; // color del vértice

        out vec3 vertexColor; // se pasa al fragment shader

        void main() {
            gl_Position = vec4(apos.x, apos.y, apos.z, 1.0);
            vertexColor = acolor;
        }
    )";

    const char *fragmentShaderSource = R"(
        #version 330 core
        in vec3 vertexColor;
        out vec4 FragColor;
        void main() {
            FragColor = vec4(vertexColor, 1.0);
        }
    )";

    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;

    // Compilacion De Vertex Shader
    int SetupVertexShader() {
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            fmt::print("ERROR: Vertex shader compilation failed:\n{}", infoLog);
            return -1;
        }
        return 0;
    }

    int SetupFragmentShader() {
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);
        {
            int success;
            char infoLog[512];
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
                fmt::print("ERROR: Fragment shader compilation failed:\n{}", infoLog);
                return -1;
            }
        }
        return 0;
    }

    // Linkear shaders en un programa

    int setupProgram() {
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        {
            int success;
            char infoLog[512];
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
                fmt::print("ERROR: Shader program linking failed:\n{}", infoLog);
                return -1;
            }
        }

        // Los shaders ya están linkeados; podemos borrarlos
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    float vertices[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f,
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2 ,3
    };

    unsigned int EBO;

    int vertexSetup(){
        glGenBuffers(1,&EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }
}
