#include "mesh.h"
#include "buffer.h"
#include "shader.h"
#include "state.h"

void Mesh::AddBuffer(const std::shared_ptr<Buffer>& buffer,
	const std::shared_ptr<Shader>& shader)
{
	if (!shader) pairs.push_back(std::make_pair(buffer, State::defaultShader));
	else         pairs.push_back(std::make_pair(buffer, shader));
}

size_t Mesh::GetNumBuffers() const
{
	return pairs.size();
}

const std::shared_ptr<Buffer>& Mesh::GetBuffer(size_t index) const
{
	return pairs.at(index).first;
}

std::shared_ptr<Buffer>& Mesh::GetBuffer(size_t index)
{
	return pairs.at(index).first;
}

void Mesh::Draw()
{
	// Draw all buffers with their shader
	for (auto pair : pairs)
	{
		// Activate shader of each buffer
		pair.second->Use();
		
		// Calculate MVP matrix
		glm::mat4 mvp = State::modelMatrix * State::viewMatrix * State::projectionMatrix;
		int loc = pair.second->GetLocation("MVP");
		pair.second->SetMatrix(loc, mvp);

		// Draw buffer
		pair.first->Draw(*pair.second);
	}
}
