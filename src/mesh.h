#pragma once

#include "common.h"
#include "material.h"
#include <vector>

class Buffer;
class Mesh;
class Shader;

typedef std::shared_ptr<Mesh> MeshPtr;
typedef std::pair<std::shared_ptr<Buffer>, std::shared_ptr<Shader>> BufferShaderPair;
typedef std::pair<std::shared_ptr<Buffer>, Material>                BufferMatPair;

class Mesh
{
public:
    static MeshPtr Create();
    static MeshPtr Load(const char* filename, const std::shared_ptr<Shader>& shader = nullptr);

	void AddBuffer(const std::shared_ptr<Buffer>& buffer,
		const std::shared_ptr<Shader>& shader = nullptr);
    void AddBuffer(const std::shared_ptr<Buffer>& buffer, const Material& material);

	size_t GetNumBuffers() const;
	const std::shared_ptr<Buffer>& GetBuffer(size_t index) const;
	      std::shared_ptr<Buffer>& GetBuffer(size_t index);
    const Material& GetMaterial(size_t index) const;
          Material& GetMaterial(size_t index);

	void Draw();

private:
    Mesh() {}

	std::vector<BufferShaderPair> m_bufferShaderPairs; // P2
    std::vector<BufferMatPair>    m_bufferMatPairs;    // P3
};
