#pragma once

#include "common.h"

struct Vertex
{
	Vertex(const glm::vec3& pos) : pos(pos) {}
	Vertex(const glm::vec3& pos, const glm::vec2& tex) : pos(pos), tex(tex) {}
	glm::vec3 pos;
    glm::vec2 tex;
	glm::vec3 normal;
};
