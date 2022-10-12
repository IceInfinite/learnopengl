#include "texture_test.h"

#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "index_buffer.h"
#include "renderer.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

namespace test {

TextureTest::TextureTest()
    : translation_a_(100.0f, 100.0f, 0.0f),
      translation_b_(200.0f, 200.0f, 0.0f) {
  // clang-format off
    float positions[] = {
      -50.0f, -50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  
       50.0f, -50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
       50.0f,  50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 
      -50.0f,  50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

      100.0f, -50.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  
      200.0f, -50.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 
      200.0f,  50.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 
      100.0f,  50.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f
  };

  unsigned int indices[] = {
      0, 1, 2, 
      2, 3, 0,

      4, 5, 6,
      6, 7, 4
  };
  // clang-format on

  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  va_ = std::make_unique<VertexArray>();
  vb_ = std::make_unique<VertexBuffer>(positions, 8 * 9 * sizeof(float));
  ib_ = std::make_unique<IndexBuffer>(indices, 12);

  layout_ = std::make_unique<VertexBufferLayout>();
  layout_->Push<float>(2);  // position
  layout_->Push<float>(4);  // color
  layout_->Push<float>(2);  // texture coord
  layout_->Push<float>(1);  // texture index
  va_->AddLayout(*vb_, *layout_);

  // Working Directory($(ProjectDir))
  shader_ = std::make_unique<Shader>("res/shaders/basic.shader");

  proj_ = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
  view_ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

  //"res/pictures/ChernoLogo.png"
  //"res/pictures/stackunderflow.png"
  texture_[0] = std::make_unique<Texture>("res/pictures/ChernoLogo.png");
  texture_[1] = std::make_unique<Texture>("res/pictures/stackunderflow.png");

  shader_->Bind();
  texture_[0]->Bind(0);
  texture_[1]->Bind(1);
  int texture_index[] = {0, 1};
  shader_->SetUniform1iv("u_textures", 2, texture_index);
}

TextureTest::~TextureTest() {
  shader_->Unbind();
  va_->Unbind();
  vb_->Unbind();
  ib_->Unbind();
  texture_[0]->Unbind();
  texture_[1]->Unbind();
}

void TextureTest::OnUpdate(float deltatme) {}

void TextureTest::OnRender() {
  model_[0] = glm::translate(glm::mat4(1.0f), translation_a_);
  model_[1] = glm::translate(glm::mat4(1.0f), translation_b_);
  glm::mat4 mvps[2];
  mvps[0] = proj_ * view_ * model_[0];
  mvps[1] = proj_ * view_ * model_[1];
  // shader_->SetUniformMat4("u_mvp0", mvp0);
  //  shader_->SetUniformMat4("u_mvp1", mvp1);
  shader_->SetUniformMat4fv("u_mvps", 2, mvps);
  Renderer::Draw(*va_, *ib_, *shader_);
}

void TextureTest::OnImGuiRender() {
  ImGui::SliderFloat3("TranslationA", &translation_a_.x, 0.0f, 960.0f);
  ImGui::SliderFloat3("TranslationB", &translation_b_.x, 0.0f, 960.0f);
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

}  // namespace test
