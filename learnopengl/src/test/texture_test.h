#ifndef TEXTURE_TEST_H_
#define TEXTURE_TEST_H_

#include <memory>

#include "glm/glm.hpp"
#include "index_buffer.h"
#include "shader.h"
#include "test.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

namespace test {

class TextureTest : public Test {
 public:
  TextureTest();
  ~TextureTest() override;

  void OnUpdate(float deltatme) override;
  void OnRender() override;
  void OnImGuiRender() override;

 private:
  std::unique_ptr<VertexArray> va_;
  std::unique_ptr<VertexBuffer> vb_;
  std::unique_ptr<IndexBuffer> ib_;
  std::unique_ptr<VertexBufferLayout> layout_;
  std::unique_ptr<Shader> shader_;
  std::unique_ptr<Texture> texture_[2];

  glm::mat4 proj_;
  glm::mat4 view_;
  glm::mat4 model_[2];

  glm::vec3 translation_a_;
  glm::vec3 translation_b_;

};

}  // namespace test

#endif  // TEXTURE_TEST_H_
