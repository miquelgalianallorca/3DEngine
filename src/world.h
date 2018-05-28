#pragma once

#include "common.h"
#include <vector>

class Camera;
class Entity;

class World
{
public:
	void AddEntity(const std::shared_ptr<Entity>& entity);
	void RemoveEntity(const std::shared_ptr<Entity>& entity);
	
	size_t GetNumEntities() const { return entities.size(); }
	
	const std::shared_ptr<Entity>& GetEntity(size_t index) const;
	      std::shared_ptr<Entity>& GetEntity(size_t index);
	
	void Update(float deltaTime);
	void Draw();

private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Camera>> cameras;
};