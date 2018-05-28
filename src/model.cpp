#include "model.h"
#include "mesh.h"
#include "state.h"

Model::Model(const std::shared_ptr<Mesh>& mesh) :
	Entity(),
	mesh(mesh)
{}

void Model::Draw()
{
	// Set Model matrix
	glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), GetPosition());
	
	// ??
	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), GetRotation().x, glm::vec3(1, 0, 0));
	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), GetRotation().y, glm::vec3(0, 1, 0));
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), GetRotation().z, glm::vec3(0, 0, 1));
	glm::mat4 rotateMat = rotateX * rotateY * rotateZ;
	
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), GetScale());
	
	glm::mat4 model = translateMat * rotateMat * scaleMat;
	State::modelMatrix = model;

	// Draw mesh
	mesh->Draw();
}
