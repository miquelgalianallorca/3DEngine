#include "buffer.h"
#include "shader.h"
#include "vertex.h"


BufferPtr Buffer::Create(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indexes)
{
	// We could check in index and vertex arrays are correct
	// (non-negative, <index.length) but it's slow and not necessary
	// in this case.
	std::shared_ptr<Buffer> buffer(new Buffer(vertices, indexes),
		[](Buffer* p) { delete p; });
	return buffer;
}

// Store arrays in VRAM
Buffer::Buffer(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indexes)
{
	// Vertex buffer
	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
		vertices.data(), GL_STATIC_DRAW);

	// Index buffer
	glGenBuffers(1, &m_indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indexes.size(),
		indexes.data(), GL_STATIC_DRAW);

	m_indexLength = indexes.size();
}

Buffer::~Buffer()
{
	// Clear VRAM
	glDeleteBuffers(1, &m_vertexBufferId);
	glDeleteBuffers(1, &m_indexBufferId);
}

void Buffer::Draw(const Shader& shader) const
{
	// Bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);

	shader.SetupAttribs();
	glDrawElements(GL_TRIANGLES, m_indexLength, GL_UNSIGNED_SHORT, nullptr);
}
