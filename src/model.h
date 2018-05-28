#pragma once

#include "entity.h"

class Mesh;

class Model : public Entity
{
public:
	Model(const std::shared_ptr<Mesh>& mesh);
	virtual void Draw() override;

private:
	std::shared_ptr<Mesh> mesh;
};
