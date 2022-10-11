#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

#include "vertex_buffer.h"

class VertexBufferLayout;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddLayout(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
	unsigned int id_;
};

#endif // VERTEX_ARRAY_H_
