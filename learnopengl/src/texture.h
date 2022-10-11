#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>

class Texture
{
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int width() const { return width_; }
	int height() const { return height_; }

private:
	unsigned int id_;
	unsigned char* file_buffer_;
	int width_;
	int height_;
	int Bpp_; // Byte per pixel
};

#endif // TEXTURE_H_
