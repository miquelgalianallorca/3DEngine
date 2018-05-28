#pragma once

#include "entity.h"

class Camera : public Entity
{
public:
	const glm::mat4&  GetProjection() const { return projection; }
	const glm::ivec4& GetViewport()   const { return viewport;   }
	const glm::vec3&  GetClearColor() const { return clearColor; }
	
	void setProjection(const glm::mat4& proj)  { projection = proj;  }
	void setViewport(const glm::ivec4& vp)     { viewport = vp;      }
	void setClearColor(const glm::vec3& color) { clearColor = color; }

	void Prepare();

private:
	glm::mat4  projection;
	glm::ivec4 viewport;
	glm::vec3  clearColor;
};