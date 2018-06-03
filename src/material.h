#pragma once

#include "common.h"

class Texture;
class Shader;

class Material
{
public:
    Material(const std::shared_ptr<Texture>& tex = nullptr,
        const std::shared_ptr<Shader>& shader = nullptr);

    const std::shared_ptr<Shader>&  GetShader()  const { return m_shader;  }
          std::shared_ptr<Shader>&  GetShader()        { return m_shader;  }
    const std::shared_ptr<Texture>& GetTexture() const { return m_texture; }
    
    void SetShader(const std::shared_ptr<Shader>& shader) { m_shader = shader; }
    void SetTexture(const std::shared_ptr<Texture>& tex)  { m_texture = tex;   }
    
    void Prepare();

private:
    std::shared_ptr<Shader>  m_shader;
    std::shared_ptr<Texture> m_texture;
};
