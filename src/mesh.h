#pragma once

#include "common.h"
#include <vector>

class Buffer;
class Shader;

typedef std::pair<std::shared_ptr<Buffer>, std::shared_ptr<Shader>> Pair;

class Mesh
{
public:
	void AddBuffer(const std::shared_ptr<Buffer>& buffer,
		const std::shared_ptr<Shader>& shader = nullptr);
	size_t GetNumBuffers() const;
	const std::shared_ptr<Buffer>& GetBuffer(size_t index) const;
	std::shared_ptr<Buffer>& GetBuffer(size_t index);
	void Draw();

private:
	std::vector<Pair> pairs;
};
