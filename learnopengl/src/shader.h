#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader {
 public:
  Shader(const std::string& filepath);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  void SetUniform1i(const std::string& name, int v0);
  void SetUniform1f(const std::string& name, float v0);

  void SetUniform4f(const std::string& name,
                    float v0,
                    float v1,
                    float v2,
                    float v3);
  void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

 private:
  struct ShaderSource {
    std::string vertex_shader;
    std::string fragment_shader;
  };

 private:
  static ShaderSource ParseShader(const std::string& filepath);
  static unsigned int CompileShader(unsigned int type,
                                    const std::string& shader_source);
  static unsigned int CreateShader(const std::string& vertex_shader,
                                   const std::string& fragment_shader);

  int GetUniformLocation(const std::string& name) const;

 private:
  unsigned int id_;
  ShaderSource source_;
  mutable std::unordered_map<std::string, int> uniform_location_cache_;
};

#endif  // SHADER_H_
