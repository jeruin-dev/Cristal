#ifndef TRIANGEL_H
#define TRIANGEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/base.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace triangel {
const char *vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 apos;   // posición del vértice
layout (location = 1) in vec3 acolor; // color del vértice

out vec3 vertexColor; // se pasa al fragment shader

void main() {
    gl_Position = vec4(apos, 1.0);
    vertexColor = acolor;
}
)";

const char *fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(vertexColor, 1.0); // color naranja
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
    // posiciones        // colores (RGB)
     0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // vértice superior (rojo)
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // vértice inferior izq (verde)
     0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // vértice inferior der (azul)
};
unsigned int VBO, VAO;

void setupBuffers() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // Bind del VAO (guarda la configuración de atributos)
  glBindVertexArray(VAO);

  // Subir datos al VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Decirle a OpenGL cómo interpretar los datos del VBO (atributo 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Desbinds opcionales
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
void setup() {
  SetupVertexShader();
  SetupFragmentShader();
  setupProgram();
  setupBuffers();
}
void render(int width, int height) {
  glUseProgram(shaderProgram);

  /*float aspect = (float)width / (float)height;

  glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -0.5f / aspect, 1.0f / aspect);

  int projLoc = glGetUniformLocation(shaderProgram, "projection");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));*/

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

} // namespace triangel

#endif
