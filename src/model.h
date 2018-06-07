#pragma once

#include "entity.h"

class Mesh;
class Model;

typedef std::shared_ptr<Model> ModelPtr;

class Model : public Entity
{
public:
    static ModelPtr Create(const std::shared_ptr<Mesh>& mesh);
	virtual void Draw() override;

protected:
    Model(const std::shared_ptr<Mesh>& mesh);

private:
    std::shared_ptr<Mesh> mesh;
};
