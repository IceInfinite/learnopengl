#include "vertex_array.h"

#include "renderer.h"
#include "vertex_buffer_layout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &id_));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &id_));
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(id_));
}
void VertexArray::Unbind() const
{

	GLCall(glBindVertexArray(0));
}

void VertexArray::AddLayout(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const std::vector<VertexBufferElement>& elements = layout.GetElements();
	int offset = 0;
	for (size_t i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), reinterpret_cast<const void*>(offset)));
		offset += elements[i].count * VertexBufferElement::GetSizeOfType(element.type);
	}
}