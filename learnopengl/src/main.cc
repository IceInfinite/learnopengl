#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "index_buffer.h"
#include "renderer.h"
#include "shader.h"
#include "test/clear_color_test.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

int main() {
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  // GL 3.3 + GLSL 330
  const char* glsl_version = "#version 330";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
  if (!window)
    return -1;

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);  // Enable vsync

  if (glewInit() != GLEW_OK)
    std::cout << "Glew init error!" << std::endl;

  std::cout << glGetString(GL_VERSION) << std::endl;
  {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    Renderer renderer;
    test::ClearColorTest clear_color_test;

    while (!glfwWindowShouldClose(window)) {
      renderer.Clear();
      clear_color_test.OnUpdate(0.0f);
      clear_color_test.OnRender();

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      clear_color_test.OnImguiRender();

      // Rendering
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      // Swap fornt and back buffers
      glfwSwapBuffers(window);

      // Poll for and process events
      glfwPollEvents();
    }

  }  // Ensure class destruction before context is deleted, avoid getting error
     // by glGetError func

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);

  glfwTerminate();
  return 0;
}