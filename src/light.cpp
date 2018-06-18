#include "light.h"
#include "shader.h"

LightPtr Light::Create(Type type, glm::vec3 color, float attenuation)
{
	std::shared_ptr<Light> light(new Light(type, color, attenuation), [](Light* p) { delete p; });
	return light;
}

void Light::Prepare(int index, std::shared_ptr<Shader>& shader) const
{
	// Write light info in shader (data in observer space)
	// ...
}
