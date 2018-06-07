#pragma once

#include "common.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;

class Entity
{
public:
	const std::string& GetName()       const { return m_name;     }
	const glm::vec3&   GetPosition()   const { return m_position; }
	const glm::vec3&   GetRotation()   const { return m_euler;	  }
	const glm::vec3&   GetScale()      const { return m_scale;    }
	const glm::quat&   GetQuaternion() const { return m_quat;     }

	void        SetName(const std::string name)   { m_name = name;    }
	void        SetPosition(const glm::vec3& pos) { m_position = pos; }
	const void  SetRotation(const glm::vec3& rot);
	void        SetScale(const glm::vec3& scale)  { m_scale = scale;  }
	const void  SetQuaternion(const glm::quat& q);

	void Move(const glm::vec3& vec);

	virtual void Update(float deltaTime) {}
	virtual void Draw() {}

protected:
    Entity() {}
    virtual ~Entity() {}

private:
	glm::vec3 m_position;
	glm::vec3 m_euler; // Rotation in euler angles
	glm::quat m_quat;  // Rotation quaternion
	glm::vec3 m_scale;

	std::string m_name;
};