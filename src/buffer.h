#pragma once

#include "common.h"
#include <vector>

class  Buffer;
class  Shader;
struct Vertex;

typedef std::shared_ptr<Buffer> BufferPtr;

class Buffer
{
public:
	static BufferPtr Create(const std::vector<Vertex>& vertices,
		const std::vector<uint16_t>& indexes);
	
	void Draw(const Shader& shader) const;

protected:
	Buffer(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indexes);
	~Buffer();

private:
	uint32_t m_vertexBufferId, m_indexBufferId;
	//std::array<uint32_t, 2> m_ids;
	
	// For glDrawArrays
	size_t m_indexLength;
};