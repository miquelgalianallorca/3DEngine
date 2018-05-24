#include "buffer.h"
#include "shader.h"
#include "vertex.h"

// Store arrays in VRAM
Buffer::Buffer(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indexes)
{
	// Vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
		vertices.data(), GL_STATIC_DRAW);

	// Index buffer
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indexes.size(),
		indexes.data(), GL_STATIC_DRAW);

	indexLength = indexes.size();
}

Buffer::~Buffer()
{
	// Clear VRAM
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Buffer::Draw(const Shader& shader) const
{
	// Bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	shader.SetupAttribs();
	glDrawElements(GL_TRIANGLES, indexLength, GL_UNSIGNED_SHORT, nullptr);
}
