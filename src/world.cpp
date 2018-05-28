#include "world.h"
#include "camera.h"
#include <algorithm>

void World::AddEntity(const std::shared_ptr<Entity>& entity)
{
	entities.push_back(entity);

	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(entity);
	if (camera) cameras.push_back(camera);
}

void World::RemoveEntity(const std::shared_ptr<Entity>& entity)
{
	entities.erase(std::remove(entities.begin(), entities.end(), entity));

	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(entity);
	if (camera) cameras.erase(std::remove(cameras.begin(), cameras.end(), camera));
}

const std::shared_ptr<Entity>& World::GetEntity(size_t index) const
{
	return entities.at(index);
}

std::shared_ptr<Entity>& World::GetEntity(size_t index)
{
	return entities.at(index);
}

void Update(float deltaTime)
{

}

void Draw()
{

}
