#include <ShaderProgram.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//Comporvador de errores en la compilacion de shaders
void ShaderProgram::checkShaderCompilationErrors(GLuint shader){
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS,&status);

    if (!status)
    {
      GLint length;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
      char *logStr = new char[length];
      glGetShaderInfoLog(shader, length, nullptr, logStr);
      std::cerr << "ERROR:" << logStr << std::endl;
      delete[] logStr;
      std::exit(-1);
    }
}

//Comporvador de errores en la compilacion de el programa
void ShaderProgram::checkProgramLinkingErrors(GLuint program) {
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (!status){
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *logStr = new char[length];
        glGetProgramInfoLog(program, length, nullptr, logStr);
        std::cerr << "LINKING ERROR: " << logStr << std::endl;
        delete[] logStr;
        std::exit(-1);
    }
}


void ShaderProgram::attachShader(GLuint program, const char *filename, GLenum shader_type){
    std::string source_code = read_file(filename);

    const char *source_code_as_c_str = source_code.c_str();

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source_code_as_c_str, nullptr);
    glCompileShader(shader);
    checkShaderCompilationErrors(shader);
    glAttachShader(program, shader);
    glDeleteShader(shader);
}

ShaderProgram::ShaderProgram(const char *vertex_shader, const char *fragment_shader){
    GLuint program = glCreateProgram();
    attachShader(program, vertex_shader, GL_VERTEX_SHADER);
    attachShader(program, fragment_shader, GL_FRAGMENT_SHADER);
    glLinkProgram(program);
    checkProgramLinkingErrors(program);
}
