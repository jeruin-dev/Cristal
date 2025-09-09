#include <Render.hpp>
#include <iostream>
#include <fstream>

//Variables
float vertices[] = {
    0.0f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
};

std::string Render::read_file(const char *filename){
    std::ifstream fin(filename);

    if (fin.fail()) {
      std::cerr << "Unable to open shader file: " << filename << std::endl;
      std::exit(-1);
    }
    return std::string(std::istreambuf_iterator<char>(fin),std::istreambuf_iterator<char>());
}

void Render::checkShaderCompilationErrors(GLuint shader) {
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

void Render::checkProgramLinkingErrors(GLuint program) {
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

void Render::attachShader(GLuint program, const char *filename, GLenum shader_type){
    std::string source_code = read_file(filename);

    const char *source_code_as_c_str = source_code.c_str();

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source_code_as_c_str, nullptr);
    glCompileShader(shader);
    checkShaderCompilationErrors(shader);
    glAttachShader(program, shader);
    glDeleteShader(shader);
}

void Render::RenderOnInitialize(){
    program = glCreateProgram();
    attachShader(program, "source/shaders/triangle.vert", GL_VERTEX_SHADER);
    attachShader(program, "source/shaders/red.frag", GL_FRAGMENT_SHADER);
    glLinkProgram(program);
    checkProgramLinkingErrors(program);

    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices, GL_STATIC_DRAW );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Render::OnDraw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    glBindVertexArray(vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL ERROR " << err << " after glDrawArrays" << std::endl;
    }
}

void Render::onDestroy() {
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(1, &VBO);
}
