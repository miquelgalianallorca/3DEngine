#pragma once

#include "common.h"

class Texture
{
public:
    static std::shared_ptr<Texture>	Load(const char* filename);
    
    uint32_t          GetId()   const { return m_id;   }
    const glm::ivec2& GetSize() const { return m_size; }
    
    void Bind() const;

private:
    Texture(const char* filename);
    ~Texture();

    uint32_t   m_id;
    glm::ivec2 m_size;
};
