#pragma once

#include "common.h"
#include <functional>

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::function<void(Entity&, float)> EntityCallback;

class Entity
{
public:
	const std::string&    GetName()       const { return m_name;     }
	const glm::vec3&      GetPosition()   const { return m_position; }
	const glm::vec3&      GetRotation()   const { return m_euler;	 }
	const glm::vec3&      GetScale()      const { return m_scale;    }
	const glm::quat&      GetQuaternion() const { return m_quat;     }
	const EntityCallback& GetCallback()   const { return m_callback; }

	void       SetName(const std::string name)   { m_name     = name;  }
	void       SetPosition(const glm::vec3& pos) { m_position = pos;   }
	const void SetRotation(const glm::vec3& rot);
	void       SetScale(const glm::vec3& scale)  { m_scale    = scale; }
	const void SetQuaternion(const glm::quat& q);
	void       SetCallback(const EntityCallback& callback) { m_callback = callback; }

	void Move(const glm::vec3& vec);

	virtual void Update(float deltaTime) {}
	// Hidden update not intended for the user
	// Does normal update and calls callback
	void _Update(float deltaTime);
	
	virtual void Draw() {}

protected:
    Entity() {}
    virtual ~Entity() {}

private:
	glm::vec3   m_position;
	glm::vec3   m_euler;    // Rotation in euler angles
	glm::quat   m_quat;     // Rotation quaternion
	glm::vec3   m_scale;
	std::string m_name;

	EntityCallback m_callback;
};

inline void Entity::_Update(float deltaTime)
{
	if (m_callback) m_callback(*this, deltaTime);
	Update(deltaTime);
}