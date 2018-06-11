#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

using std::cout;
using std::endl;

std::shared_ptr<Texture> Texture::Load(const char* filename)
{
    std::shared_ptr<Texture> texture(new Texture(filename), [](Texture* p) { delete p; });
    if (texture->GetId() < 0)
        return nullptr;
    
    return texture;
}

Texture::Texture(const char* filename) :
    m_id(-1),
    m_size(glm::vec2(0.f, 0.f))
{
    // Load image (RGBA)
    stbi_set_flip_vertically_on_load(true);
    unsigned char *buffer = stbi_load(filename, &m_size.x, &m_size.y, nullptr, 4);
    if (!buffer)
    {
        cout << "Couldn't load image." << endl;
        return;
    }

    // Generate texture (Linear filtering) in VRAM
    glGenTextures(1, &m_id);

    // Filtering mode: trilinear
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Generate image and mipmapping
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Release from RAM
    stbi_image_free(buffer);
}

Texture::~Texture()
{
    // Release from VRAM
	glDeleteTextures(1, &m_id);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}
