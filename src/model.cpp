#include "model.h"
#include "mesh.h"
#include "state.h"

ModelPtr Model::Create(const std::shared_ptr<Mesh>& mesh)
{
	if (!mesh) return nullptr;

    std::shared_ptr<Model> model(new Model(mesh), [](Model* p) { delete p; });
    return model;
}

Model::Model(const std::shared_ptr<Mesh>& mesh) :
	Entity(),
	mesh(mesh)
{
    SetPosition(glm::vec3(0.f, 0.f, 0.f));
    SetRotation(glm::vec3(0.f, 0.f, 0.f));
    SetScale   (glm::vec3(1.f, 1.f, 1.f));
}

void Model::Draw()
{
	// Set Model matrix
	glm::mat4 translateMat = glm::translate(glm::mat4(1.f), GetPosition());
	glm::mat4 rotateMat    = glm::rotate   (glm::mat4(1.f), glm::angle(GetQuaternion()), glm::axis(GetQuaternion()));
	glm::mat4 scaleMat     = glm::scale    (glm::mat4(1.f), GetScale());
	
	glm::mat4 model = translateMat * rotateMat * scaleMat;
	State::modelMatrix = model;

	// Draw mesh
	mesh->Draw();
}
