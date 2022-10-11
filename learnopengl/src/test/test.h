#ifndef TEST_TEST_H_
#define TEST_TEST_H_

namespace test {

class Test {
 public:
  virtual ~Test() {}
  virtual void OnUpdate(float delta_time) = 0;
  virtual void OnRender() = 0;
  virtual void OnImguiRender() = 0;
};

}  // namespace test

#endif  // TEST_TEST_H_
