#include "texture.h"

#include <GL/glew.h>

#include "renderer.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& filepath)
    : id_(0), file_buffer_(nullptr), width_(0), height_(0), Bpp_(0) {
  stbi_set_flip_vertically_on_load(1);
  file_buffer_ = stbi_load(filepath.c_str(), &width_, &height_, &Bpp_, 4);

  GLCall(glGenTextures(1, &id_));
  // GLCall(glActiveTexture(GL_TEXTURE0 + id_ - 1));
  GLCall(glBindTexture(GL_TEXTURE_2D, id_));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  // GLCall(glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  // GLCall(glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  // GLCall(glTextureParameteri(id_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  // GLCall(glTextureParameteri(id_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA,
                      GL_UNSIGNED_BYTE, static_cast<void*>(file_buffer_)));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

  if (file_buffer_)
    stbi_image_free(static_cast<void*>(file_buffer_));
}

Texture::~Texture() {
  GLCall(glDeleteTextures(1, &id_));
}

void Texture::Bind(unsigned int slot) const {
  GLCall(glActiveTexture(GL_TEXTURE0 + slot));
  GLCall(glBindTexture(GL_TEXTURE_2D, id_));
}

void Texture::Unbind() const {
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
