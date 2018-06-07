#pragma once

#include "common.h"
#include "entity.h"
#include <vector>

class Camera;
class World;

typedef std::shared_ptr<World> WorldPtr;

class World
{
public:
	static WorldPtr Create();

	const EntityPtr FindEntity(const std::string& name) const;
	EntityPtr FindEntity(const std::string& name);

	void AddEntity(const std::shared_ptr<Entity>& entity);
	void RemoveEntity(const std::shared_ptr<Entity>& entity);
	
	size_t GetNumEntities() const { return entities.size(); }
	
	const std::shared_ptr<Entity>& GetEntity(size_t index) const;
	      std::shared_ptr<Entity>& GetEntity(size_t index);
	
	void Update(float deltaTime);
	void Draw();

private:
	World();
	~World() {}

	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Camera>> cameras;
};