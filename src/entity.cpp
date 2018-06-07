#include "entity.h"

const void Entity::SetRotation(const glm::vec3& rot)
{
	m_euler = rot;
	m_quat = glm::quat(rot);
}

const void Entity::SetQuaternion(const glm::quat& q)
{
	m_quat = q;
	m_euler = glm::degrees(glm::eulerAngles(q));
}

void Entity::Move(const glm::vec3& vec)
{
	m_position += m_quat * vec;
}
