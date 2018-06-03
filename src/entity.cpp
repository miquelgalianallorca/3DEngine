#include "entity.h"

void Entity::Move(const glm::vec3& vec)
{
	// Constructs quaternion with euler angles (in radians)
	glm::quat quat = glm::quat(rotation);
	position += quat * vec;
}
