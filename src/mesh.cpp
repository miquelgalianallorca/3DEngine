#include "mesh.h"
#include "buffer.h"
#include "shader.h"
#include "state.h"

MeshPtr Mesh::Create()
{
    std::shared_ptr<Mesh> mesh(new Mesh(), [](Mesh* p) { delete p; });
    return mesh;
}

void Mesh::AddBuffer(const std::shared_ptr<Buffer>& buffer,
	const std::shared_ptr<Shader>& shader)
{
	if (!shader) m_bufferShaderPairs.push_back(std::make_pair(buffer, State::defaultShader));
	else         m_bufferShaderPairs.push_back(std::make_pair(buffer, shader));
}

void Mesh::AddBuffer(const std::shared_ptr<Buffer>& buffer, const Material& material)
{
    // No storing shaders directly, only a material per buffer
    m_bufferMatPairs.push_back(std::make_pair(buffer, material));
}

size_t Mesh::GetNumBuffers() const
{
	return m_bufferShaderPairs.size();
}

const std::shared_ptr<Buffer>& Mesh::GetBuffer(size_t index) const
{
	return m_bufferShaderPairs.at(index).first;
}

std::shared_ptr<Buffer>& Mesh::GetBuffer(size_t index)
{
	return m_bufferShaderPairs.at(index).first;
}

const Material& Mesh::GetMaterial(size_t index) const
{
    return m_bufferMatPairs.at(index).second;
}

Material& Mesh::GetMaterial(size_t index)
{
    return m_bufferMatPairs.at(index).second;
}

void Mesh::Draw()
{
    for (auto& pair : m_bufferMatPairs)
    {
        // Prepare material
        pair.second.Prepare();
        // Draw buffer with material's shader
        pair.first->Draw(*pair.second.GetShader());
    }
}
