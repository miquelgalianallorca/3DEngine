#pragma once

#include "common.h"
#include <vector>

class Shader;
class Light;

class State
{
public:
	static std::shared_ptr<Shader>             defaultShader;
	static glm::mat4                           projectionMatrix;
	static glm::mat4                           viewMatrix;
	static glm::mat4                           modelMatrix;
	static glm::vec3                           ambient;
	static std::vector<std::shared_ptr<Light>> lights;

private:
	State()  {}
	~State() {}
};
