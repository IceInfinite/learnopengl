#ifndef VERTEX_BUFFER_LAYOUT_H_
#define VERTEX_BUFFER_LAYOUT_H_

#include <GL/glew.h>

#include <vector>

#include "renderer.h"

struct VertexBufferElement {
  VertexBufferElement(unsigned int i_type,
                      unsigned int i_count,
                      unsigned char i_normalized)
      : type(i_type), count(i_count), normalized(i_normalized) {}
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static int GetSizeOfType(unsigned int type) {
    switch (type) {
      case (GL_FLOAT):
        return sizeof(float);
      case (GL_UNSIGNED_BYTE):
        return sizeof(unsigned char);
      case (GL_UNSIGNED_INT):
        return sizeof(unsigned int);
    }
    ASSERT(false);
    return 0;
  }
};

class VertexBufferLayout {
 public:
  VertexBufferLayout() : stride_(0) {}

  template <typename T>
  void Push(unsigned int count) {
    // static_assert(false);
  }

  template <>
  void Push<float>(unsigned int count) {
    elements_.emplace_back(GL_FLOAT, count, GL_FALSE);
    stride_ += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
  }

  template <>
  void Push<unsigned int>(unsigned int count) {
    elements_.emplace_back(GL_UNSIGNED_INT, count, GL_TRUE);
    stride_ += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
  }

  template <>
  void Push<unsigned char>(unsigned int count) {
    stride_ += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
  }

  int GetStride() const { return stride_; }
  std::vector<VertexBufferElement> GetElements() const { return elements_; }

 private:
  std::vector<VertexBufferElement> elements_;
  int stride_;
};

#endif  // VERTEX_BUFFER_LAYOUT_H_
