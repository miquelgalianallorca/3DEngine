#include "entity.h"

void Entity::Move(const glm::vec3& vec)
{
	// Constructs quaternion with euler angles (in radians)
	glm::quat quat = glm::quat(rotation);
	// glm::quat qPitch = glm::angleAxis(x, glm::vec3(1, 0, 0))
	position += quat * vec;
}
