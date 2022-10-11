#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int GetCount() const;

private:
	unsigned int id_;
	unsigned int count_;
};

#endif // INDEX_BUFFER_H_
