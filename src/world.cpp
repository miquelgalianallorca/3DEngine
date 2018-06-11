#include "world.h"
#include "camera.h"
#include <algorithm>

WorldPtr World::Create()
{
	std::shared_ptr<World> world(new World(), [](World* p) { delete p; });
	return world;
}

World::World()
{
	// ...
}

const EntityPtr World::FindEntity(const std::string& name) const
{
	auto entity = std::find_if(entities.begin(), entities.end(),
		[name](EntityPtr e) { return e->GetName() == name; });
	return *entity;
}

EntityPtr World::FindEntity(const std::string& name)
{
	auto entity = std::find_if(entities.begin(), entities.end(),
		[name](EntityPtr e) { return e->GetName() == name; });
	return *entity;
}

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

void World::Update(float deltaTime)
{
    for (auto entity : entities)
    {
        entity->_Update(deltaTime);
    }
}

void World::Draw()
{
    for (auto camera : cameras)
    {
        camera->Prepare();
        for (auto entity : entities)
        {
            entity->Draw();
        }
    }
}
