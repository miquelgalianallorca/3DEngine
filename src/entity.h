#pragma once

#include "common.h"

class Entity
{
public:
	const glm::vec3& GetPosition() const { return position; }
	const glm::vec3& GetRotation() const { return rotation;	} // puede ser quat
	const glm::vec3& GetScale()    const { return scale;    }
	
	void        SetPosition(const glm::vec3& pos) { position = pos;      }
	const void  SetRotation(const glm::vec3& rot) {	rotation = rot;      } // puede ser quat
	void        SetScale(const glm::vec3& scale)  { this->scale = scale; }

	void Move(const glm::vec3& vec);	// ver en las diapositivas

	virtual void Update(float deltaTime) {}
	virtual void Draw() {}

protected:
    Entity() {}
    virtual ~Entity() {}

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};