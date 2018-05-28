#pragma once

#include "common.h"

class Shader;

class State
{
public:
	static std::shared_ptr<Shader> defaultShader;
	static glm::mat4               projectionMatrix;
	static glm::mat4               viewMatrix;
	static glm::mat4               modelMatrix;

private:
	State()  {}
	~State() {}
};
