#include "shader.h"

#include "renderer.h"

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath) : id_(0)
{
	source_ = ParseShader(filepath);
	id_ = CreateShader(source_.vertex_shader, source_.fragment_shader);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(id_));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(id_));
}
void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

Shader::ShaderSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::stringstream ss[2];
	enum class ShaderType
	{
		None = -1,
		Vertex = 0,
		Fragment = 1
	};

	ShaderType type = ShaderType::None;
	std::string line;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::Vertex;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::Fragment;
		}
		else
		{
			ss[static_cast<int>(type)] << line << "\n";
		}
	}
	stream.close();
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& shader_source)
{
	GLCall(unsigned int shader = glCreateShader(type));
	const char* src = shader_source.c_str();
	GLCall(glShaderSource(shader, 1, &src, nullptr));
	GLCall(glCompileShader(shader));

	int status;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));
	if (status != GL_TRUE)
	{
		int log_length = 0;
		// glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		// char* message = (char*)alloca(sizeof(char) * log_length);
		char message[512];
		GLCall(glGetShaderInfoLog(shader, 512, &log_length, message));

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		return 0;
	}

	return shader;
}

unsigned int Shader::CreateShader(const std::string& vertex_shader, const std::string& fragment_shader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));

	int status;
	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &status));
	if (status != GL_TRUE)
	{
		int log_length = 0;
		char message[512];
		GLCall(glGetProgramInfoLog(program, 512, &log_length, message));
		std::cout << "Failed to link program!" << std::endl;
		std::cout << message << std::endl;
		return 0;
	}

	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

void Shader::SetUniform1i(const std::string& name, int v0)
{
	GLCall(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::SetUniform1f(const std::string& name, float v0)
{
	GLCall(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) const
{
	if (uniform_location_cache_.find(name) != uniform_location_cache_.end())
		return uniform_location_cache_[name];

	GLCall(int location = glGetUniformLocation(id_, name.c_str()));

	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	uniform_location_cache_[name] = location;
	return location;
}