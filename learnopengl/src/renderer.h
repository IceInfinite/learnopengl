#ifndef RENDERER_H_
#define RENDERER_H_

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

#define ASSERT(x) \
	if (!(x))     \
	__debugbreak()

#define GLCall(x)   \
	GLClearError(); \
	x;              \
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

private:
};

#endif // IndexBuffer
