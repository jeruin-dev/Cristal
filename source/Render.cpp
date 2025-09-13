#include <Render.hpp>
#include <iostream>
#include <fstream>


float vertices[] = {
    0.0f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
};


void Render::RenderOnInitialize(){
    program = glCreateProgram();
    attachShader(program, "D:/Jeruin/dev/Cristal/source/shaders/triangle.vert", GL_VERTEX_SHADER);
    attachShader(program, "D:/Jeruin/dev/Cristal/source/shaders/red.frag", GL_FRAGMENT_SHADER);
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
