#ifndef TEST_CLAER_COLOR_TEST_H_
#define TEST_CLAER_COLOR_TEST_H_

#include "test.h"

namespace test {

class ClearColorTest : public Test {
 public:
  ClearColorTest();
  ~ClearColorTest();

  void OnUpdate(float delta_time) override;
  void OnRender() override;
  void OnImGuiRender() override;

 private:
  float clear_color[4];
};

}  // namespace test

#endif  // TEST_CLAER_COLOR_TEST_H_
