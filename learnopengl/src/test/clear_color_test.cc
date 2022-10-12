#include "clear_color_test.h"

#include <GL/glew.h>

#include "imgui/imgui.h"
#include "renderer.h"

namespace test {

ClearColorTest::ClearColorTest() : clear_color{0.0f, 0.0f, 1.0f, 1.0f} {}

ClearColorTest::~ClearColorTest() {}

void ClearColorTest::OnUpdate(float delta_time) {}

void ClearColorTest::OnRender() {
  GLCall(glClearColor(clear_color[0], clear_color[1], clear_color[2],
                      clear_color[3]));
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void ClearColorTest::OnImGuiRender() {
  ImGui::ColorEdit4("color", clear_color);
}

}  // namespace test
