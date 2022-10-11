#include "vertex_buffer.h"

#include <GL/glew.h>

#include "renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
  GLCall(glGenBuffers(1, &id_));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, id_));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer() {
  GLCall(glDeleteBuffers(1, &id_));
}

void VertexBuffer::Bind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, id_));
}
void VertexBuffer::Unbind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}