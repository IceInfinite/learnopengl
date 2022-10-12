#include "renderer.h"

#include <GL/glew.h>

#include <iostream>

void GLClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

bool GLLogCall(const char* function, const char* file, int line) {
  while (unsigned int error = glGetError()) {
    std::cout << "Error: " << error << " " << function << " " << file << ":"
              << line << std::endl;
    return false;
  }
  return true;
}

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Clear() {
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va,
                    const IndexBuffer& ib,
                    const Shader& shader) {
  va.Bind();
  ib.Bind();
  shader.Bind();

  GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
