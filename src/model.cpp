#include "model.h"
#include "mesh.h"
#include "state.h"

ModelPtr Model::Create(const std::shared_ptr<Mesh>& mesh)
{
    std::shared_ptr<Model> model(new Model(mesh), [](Model* p) { delete p; });
    return model;
}

Model::Model(const std::shared_ptr<Mesh>& mesh) :
	Entity(),
	mesh(mesh)
{
    SetPosition(glm::vec3(0.f, 0.f, 0.f));
    SetRotation(glm::vec3(0.f, 0.f, 0.f));
    SetScale(glm::vec3(1.f, 1.f, 1.f));
}

void Model::Draw()
{
	// Set Model matrix
	glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), GetPosition());
	
	// ??
	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), GetRotation().x, glm::vec3(1, 0, 0));
	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), GetRotation().y, glm::vec3(0, 1, 0));
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), GetRotation().z, glm::vec3(0, 0, 1));
	glm::mat4 rotateMat = rotateZ * rotateY * rotateX;
    
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), GetScale());
	
	glm::mat4 model = translateMat * rotateMat * scaleMat;
	State::modelMatrix = model;

	// Draw mesh
	mesh->Draw();
}
