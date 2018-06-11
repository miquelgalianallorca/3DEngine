#pragma once

#include "entity.h"

class Camera;
typedef std::shared_ptr<Camera> CameraPtr;

class Camera : public Entity
{
public:
    static CameraPtr Create();

	const glm::mat4&  GetProjection() const { return projection; }
	const glm::ivec4& GetViewport()   const { return viewport;   }
	const glm::vec3&  GetClearColor() const { return clearColor; }
	
	void SetProjection(const glm::mat4& proj)  { projection = proj;  }
	void SetViewport  (const glm::ivec4& vp)   { viewport = vp;      }
	void SetClearColor(const glm::vec3& color) { clearColor = color; }

	void Prepare();

protected:
	Camera()  {}
	virtual ~Camera() {}

private:
	glm::mat4  projection;
	glm::ivec4 viewport;
	glm::vec3  clearColor;
};