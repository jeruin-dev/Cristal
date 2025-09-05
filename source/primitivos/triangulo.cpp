
#ifndef TRIANGEL_H
#define TRIANGEL_H


#include <fmt/base.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>


namespace geometria {


// =========================================================
// Clase Shader (RAII para un solo shader)
// =========================================================
class Shader {
    GLuint id;
public:
    Shader(GLenum type, const char* source) {
        id = glCreateShader(type);
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        int success;
        char infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id, 512, nullptr, infoLog);
            fmt::print("ERROR::SHADER::COMPILATION_FAILED\n{}\n", infoLog);
            throw std::runtime_error("Shader compilation failed");
        }
    }

    GLuint getID() const { return id; }

    ~Shader() { glDeleteShader(id); }
};

// =========================================================
// Clase ShaderProgram (RAII para el programa de shaders)
// =========================================================
class ShaderProgram {
    GLuint id;
public:
    ShaderProgram(const char* vertexSrc, const char* fragmentSrc) {
        Shader vs(GL_VERTEX_SHADER, vertexSrc);
        Shader fs(GL_FRAGMENT_SHADER, fragmentSrc);

        id = glCreateProgram();
        glAttachShader(id, vs.getID());
        glAttachShader(id, fs.getID());
        glLinkProgram(id);

        int success;
        char infoLog[512];
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 512, nullptr, infoLog);
            fmt::print("ERROR::PROGRAM::LINKING_FAILED\n{}\n", infoLog);
            throw std::runtime_error("Program linking failed");
        }
    }

    void use() const { glUseProgram(id); }

    GLuint getID() const { return id; }

    void setUniform3f(const std::string& name, float x, float y, float z) const {
        GLint loc = glGetUniformLocation(id, name.c_str());
        glUniform3f(loc, x, y, z);
    }

    ~ShaderProgram() { glDeleteProgram(id); }
};

// =========================================================
// Clase Mesh (RAII para VBO/VAO)
// =========================================================
class Mesh {
    GLuint VAO, VBO;
    GLsizei vertexCount;
public:
    Mesh(const std::vector<float>& vertices) {
        vertexCount = static_cast<GLsizei>(vertices.size() / 6); // 6 floats por vértice

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                     vertices.data(), GL_STATIC_DRAW);

        // atributo 0: posición
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // atributo 1: color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                              6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void draw() const {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

    ~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};

// =========================================================
// Shaders fuente
// =========================================================
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 apos;
    layout (location = 1) in vec3 acolor;

    out vec3 vertexColor;

    void main() {
        gl_Position = vec4(apos, 1.0);
        vertexColor = acolor;
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 vertexColor;
    out vec4 FragColor;

    uniform vec3 globalColor; // opcional

    void main() {
        FragColor = vec4(vertexColor * globalColor, 1.0);
    }
)";

// =========================================================
// Datos del triángulo
// =========================================================
std::vector<float> vertices = {
     // posiciones        // colores
     0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // arriba rojo
    -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // izq verde
     0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // der azul
};

// =========================================================
// Setup y Render
// =========================================================
ShaderProgram* shaderProgram;
Mesh* mesh;

void setup() {
    shaderProgram = new ShaderProgram(vertexShaderSource, fragmentShaderSource);
    mesh = new Mesh(vertices);
}

 void render() {
    shaderProgram->use();
    shaderProgram->setUniform3f("globalColor", 1.0f, 1.0f, 1.0f); // blanco → sin cambio

    mesh->draw();
}

void cleanup() {
    delete shaderProgram;
    delete mesh;
}

}   //Namespace geometria
#endif
