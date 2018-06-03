#include "material.h"
#include "shader.h"
#include "state.h"
#include "texture.h"

Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader)
{
    m_texture = tex;

    if (!shader) m_shader = State::defaultShader;
    else         m_shader = shader;
}

void Material::Prepare()
{
    // Activate shader
    m_shader->Use();

    // Write uniform vars
    glm::mat4 mvp = State::projectionMatrix * State::viewMatrix * State::modelMatrix;
    m_shader->SetMatrix(m_shader->GetLocation("MVP"), mvp);
    
    if (m_texture) m_shader->SetInt(m_shader->GetLocation("hasTexture"), 1);
    else           m_shader->SetInt(m_shader->GetLocation("hasTexture"), 0);
    
    m_shader->SetInt(m_shader->GetLocation("texSampler"), 0);

    // Bind texture
    if (m_texture) m_texture->Bind();
}
