#pragma once

#include "common.h"
#include <vector>

class Shader;
struct Vertex;

class Buffer
{
public:
	Buffer(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indexes);
	~Buffer();
	
	void Draw(const Shader& shader) const;

private:
	uint32_t vertexBuffer, indexBuffer;
	
	// For glDrawArrays
	size_t indexLength;
};