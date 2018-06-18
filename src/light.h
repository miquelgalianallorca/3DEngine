#pragma once

#include "entity.h"

class Light;
class Shader;
typedef std::shared_ptr<Light> LightPtr;

class Light : public Entity
{
public:
	enum class Type { DIRECTIONAL, POINT };
	
	static LightPtr Create(Type type, glm::vec3 color, float attenuation);

	Type             GetType()              const { return m_type;              }
	const glm::vec3& GetColor()             const { return m_color;             }
	float            GetLinearAttenuation() const { return m_linearAttenuation; }

	void SetType(Type type)               { m_type  = type;            }
	void SetColor(const glm::vec3& color) { m_color = color;           }
	void SetLinearAttenuation(float att)  { m_linearAttenuation = att; }
	
	void Prepare(int index, std::shared_ptr<Shader>& shader) const;

private:
	Light(Type type, glm::vec3 color, float attenuation) :
		m_type(type),
		m_color(color),
		m_linearAttenuation(attenuation)
	{}
	~Light() {}

	Type      m_type;
	glm::vec3 m_color;
	float     m_linearAttenuation;

	const float m_constantAttenuation  = 1.f;
	const float m_quadraticAttenuation = 0.f;
};
