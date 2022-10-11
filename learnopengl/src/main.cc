#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "vertex_buffer_layout.h"
#include "shader.h"
#include "texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
	GLFWwindow* window;
	{
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
		glfwSwapInterval(1); // Enable vsync

		if (glewInit() != GLEW_OK)
			std::cout << "Glew init error!" << std::endl;

		std::cout << glGetString(GL_VERSION) << std::endl;

		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f, // 0
			 50.0f, -50.0f, 1.0f, 0.0f, // 1
			 50.0f,  50.0f, 1.0f, 1.0f, // 2
			-50.0f,  50.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		IndexBuffer ib(indices, 6);

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddLayout(vb, layout);

		// Working Directory($(ProjectDir))
		Shader shader("res/shaders/basic.shader");
		shader.Bind();
		// std::cout << "Vertex" << std::endl;
		// std::cout << shader.GetSource().vertex_shader << std::endl;
		// std::cout << "Fragment" << std::endl;
		// std::cout << shader.GetSource().fragment_shader << std::endl;

		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

		//"res/pictures/ChernoLogo.png"
		//"res/pictures/stackunderflow.png"
		Texture texture0("res/pictures/ChernoLogo.png");
		texture0.Bind();
		shader.SetUniform1i("u_texture0", 0);

		// texture composition，use another texture unit, each machine has it's number of texture unit
		// Texture texture1("res/pictures/stackunderflow.png");
		// texture1.Bind(1);
		// shader.SetUniform1i("u_texture1", 1);

		shader.Unbind();
		va.Unbind();
		vb.Unbind();
		ib.Unbind();

		Renderer renderer;

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		float increment = -0.05f;
		glm::vec3 translation_a(100.0f, 100.0f, 0.0f);
		glm::vec3 translation_b(200.0f, 200.0f, 0.0f);
		while (!glfwWindowShouldClose(window))
		{
			// Render here
			renderer.Clear();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			{
				shader.Bind();
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translation_a);
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4("u_mvp", mvp);
				renderer.Draw(va, ib, shader);
			}

			{
				shader.Bind();
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translation_b);
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4("u_mvp", mvp);
				renderer.Draw(va, ib, shader);
			}

			// Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
			{
				ImGui::Begin("Hello, world!");   // Create a window called "Hello, world!" and append into it.

				ImGui::SliderFloat3("TranslationA", &translation_a.x, 0.0f, 960.0f);
				ImGui::SliderFloat3("TranslationB", &translation_b.x, 0.0f, 960.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

				ImGui::End();
			}

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// Swap fornt and back buffers
			glfwSwapBuffers(window);

			// Poll for and process events
			glfwPollEvents();
		}

	} // Ensure class destruction before context is deleted, avoid getting error by glGetError func

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}