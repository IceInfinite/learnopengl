#ifndef TEST_TEST_H_
#define TEST_TEST_H_

#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace test {

class Test {
 public:
  virtual ~Test() {}
  virtual void OnUpdate(float delta_time) {}
  virtual void OnRender() {}
  virtual void OnImGuiRender() {}
};

class TestMenu : public Test {
 public:
  TestMenu(Test*& current_test);
  ~TestMenu() override;

  void OnImGuiRender() override;

  template <typename T>
  void RegisterTest(const std::string& name);

 private:
  Test*& current_test_;
  std::vector<std::pair<std::string, std::function<Test*()>>> tests_;
};

// Findout why this func can not be putted in .cc file
template <typename T>
void TestMenu::RegisterTest(const std::string& name) {
  tests_.push_back(std::make_pair(name, []() { return new T(); }));
}

}  // namespace test

#endif  // TEST_TEST_H_
