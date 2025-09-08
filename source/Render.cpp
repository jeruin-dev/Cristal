#include <Render.hpp>
#include <iostream>
#include <fstream>


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
      if (!status)
      {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *logStr = new char[length];
        glGetProgramInfoLog(program, length, nullptr, logStr);
        std::cerr << "LINKING ERROR: " << logStr << std::endl;
        delete[] logStr;
        std::exit(-1);
      }
    }

    void Render::attachShader(GLuint program, const char *filename, GLenum shader_type)
      {
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
    attachShader(program, "assets/shaders/ex02_shader_introduction/triangle.vert", GL_VERTEX_SHADER);
    attachShader(program, "assets/shaders/ex02_shader_introduction/red.frag", GL_FRAGMENT_SHADER);
    glLinkProgram(program);
    checkProgramLinkingErrors(program);
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,);
    glGenVertexArrays(1, &vertex_array); // Ask GL to create a vertex array to
}

void Render::RenderOnDraw(double deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    glBindVertexArray(vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);                       // Unbind the buffer.

}
void Render::onDestroy() {
    glDeleteProgram(program);                   // Cleaning up the program we compiled and saved.
    glDeleteVertexArrays(1, &vertex_array);     // Clean up the array we allocated Params: (n: number of vertex array objects, array containing the n addresses of the objects)
}
