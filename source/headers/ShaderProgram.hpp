#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


class ShaderProgram {
    private:
        std::string read_file(const char *filename);
        void checkShaderCompilationErrors(GLuint shader);
        void checkProgramLinkingErrors(GLuint program);

    public:
       void attachShader(GLuint program, const char *filename, GLenum shader_type);
       ShaderProgram(const char *vertex_shader_file, const char *fragment_shader_file);

};
