#include "camera.h"
#include "state.h"

CameraPtr Camera::Create()
{
    std::shared_ptr<Camera> camera(new Camera(), [](Camera* p) { delete p; });
    return camera;
}

void Camera::Prepare()
{
	// Set projection matrix
	State::projectionMatrix = projection;

	// Set view matrix:
    // Rotating and translating the camera is the same as translating and rotating the vertexs
    // with the opposite direction and angle
    glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), GetPosition() * -1.f);
	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), GetRotation().x * -1.f, glm::vec3(1, 0, 0));
	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), GetRotation().y * -1.f, glm::vec3(0, 1, 0));
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), GetRotation().z * -1.f, glm::vec3(0, 0, 1));
	glm::mat4 rotationMat = rotateX * rotateY * rotateZ;
    
	State::viewMatrix = rotationMat * translationMat;
	
	// Set viewport
	glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
	glScissor (viewport.x, viewport.y, viewport.z, viewport.w);

	// Clear screen
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Camera::Update(float deltaTime)
{
	SetRotation(glm::vec3(m_pitch, 0.f, 0.f));
	SetRotation(glm::vec3(0.f, m_yaw, 0.f));
	SetRotation(glm::vec3(m_pitch, m_yaw, 0.f));
}