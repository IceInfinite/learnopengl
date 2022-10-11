#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

class VertexBuffer {
 public:
  VertexBuffer(const void* data, unsigned int size);
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;

 private:
  unsigned int id_;
};

#endif  // VERTEX_BUFFER_H_
