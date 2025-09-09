#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Render {
    private:
        //Variables
        GLuint program = 0, vertex_array = 0;
        unsigned int VBO;

        //Funciones
        std::string read_file(const char *filename);
        void checkShaderCompilationErrors(GLuint shader);
        void checkProgramLinkingErrors(GLuint program);

    public:
        //Funciones
        void attachShader(GLuint program, const char *filename, GLenum shader_type);
        void RenderOnInitialize();
        void OnDraw();
        void onDestroy();
};
