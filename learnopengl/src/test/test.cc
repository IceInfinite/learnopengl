#include "test.h"

#include "imgui/imgui.h"
#include "renderer.h"

namespace test {

TestMenu::TestMenu(Test*& current_test) : current_test_(current_test) {}

TestMenu ::~TestMenu() {}

void TestMenu::OnImGuiRender() {
  for (const auto& test : tests_) {
    if (ImGui::Button(test.first.c_str())) {
      current_test_ = test.second();
    }
  }
}

}  // namespace test