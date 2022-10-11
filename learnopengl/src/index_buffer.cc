#include "index_buffer.h"

#include <GL/glew.h>

#include "renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : count_(count) {
  GLCall(glGenBuffers(1, &id_));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int),
                      data, GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer() {
  GLCall(glDeleteBuffers(1, &id_));
}

void IndexBuffer::Bind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_));
}
void IndexBuffer::Unbind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::GetCount() const {
  return count_;
}
