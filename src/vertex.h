#pragma once

#include "common.h"

struct Vertex
{
	Vertex(const glm::vec3& _pos) : pos(_pos) {}
	glm::vec3 pos;
};
