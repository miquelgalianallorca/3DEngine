#include "camera.h"
#include "state.h"

void Camera::Prepare()
{
	// Set projection matrix
	State::projectionMatrix = projection;

	// Set view matrix
	glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), GetPosition() * -1.f);
	
	// ??
	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), GetRotation().x * -1.f, glm::vec3(1, 0, 0));
	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), GetRotation().y * -1.f, glm::vec3(0, 1, 0));
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), GetRotation().z * -1.f, glm::vec3(0, 0, 1));
	glm::mat4 rotationMat = rotateX * rotateY * rotateZ;
	
	glm::mat4 view = rotationMat * translationMat;
	State::viewMatrix = view;
	
	// Set viewport
	glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
	glScissor (viewport.x, viewport.y, viewport.z, viewport.w);
	// Clear screen
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
