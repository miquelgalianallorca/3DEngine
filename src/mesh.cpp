#include "mesh.h"
#include "buffer.h"
#include "material.h"
#include "shader.h"
#include "state.h"
#include "texture.h"
#include "utils.h"
#include "vertex.h"
#include "pugixml.hpp"
#include <iostream>

MeshPtr Mesh::Create()
{
    std::shared_ptr<Mesh> mesh(new Mesh(), [](Mesh* p) { delete p; });
    return mesh;
}

MeshPtr Mesh::Load(const char* filename, const std::shared_ptr<Shader>& shader)
{
    // Parse XML
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename);
    if (result)
    {
        // Create mesh
        std::shared_ptr<Mesh> mesh(new Mesh(), [](Mesh* p) { delete p; });

        pugi::xml_node meshNode    = doc.child("mesh");
        pugi::xml_node buffersNode = meshNode.child("buffers");
        // Iterate over buffers
        for (pugi::xml_node bufferNode = buffersNode.child("buffer"); bufferNode;
            bufferNode = bufferNode.next_sibling("buffer"))
        {
            // Material
            pugi::xml_node materialNode = bufferNode.child("material");
            std::string textureStr = materialNode.child("texture").text().as_string();
            textureStr = extractPath(filename) + textureStr;
            // Indexs
            std::string indexsStr = bufferNode.child("indices").text().as_string();
            std::vector<uint16_t> indexs = splitString<uint16_t>(indexsStr, ',');
            // Coords
            std::string coordsStr = bufferNode.child("coords").text().as_string();
            std::vector<float> coords = splitString<float>(coordsStr, ',');
            // Texcoords
            std::string texCoordsStr = bufferNode.child("texcoords").text().as_string();
            std::vector<float> texCoords = splitString<float>(texCoordsStr, ',');

            // Load vertexs
            std::vector<Vertex> vertexs;
            for (int i = 0; i < coords.size(); i+=3)
            {
                vertexs.push_back(Vertex(glm::vec3(
                    coords.at(i),
                    coords.at(i+1),
                    coords.at(i+2)
                )));
            }
            std::vector<glm::vec2> texs;
            for (int i = 0; i < texCoords.size(); i+=2)
            {
                texs.push_back(glm::vec2(texCoords.at(i), texCoords.at(i + 1)));
            }
            if (vertexs.size() != texs.size())
            {
                std::cout << "Error: Wrong mesh format in XML." << std::endl;
                return nullptr;
            }
            for (int i = 0; i < vertexs.size(); ++i)
            {
                vertexs.at(i).tex = texs.at(i);
            }
            
            // Create buffer & material
            BufferPtr  buffer  = Buffer::Create(vertexs, indexs);
            TexturePtr texture = Texture::Load(textureStr.c_str());
            Material   material(texture);
            mesh->AddBuffer(buffer, material);
        }

        return mesh;
    }
    // File could not be loaded
    else
    {
        std::cout << result.description() << std::endl;
        return nullptr;
    }
}

void Mesh::AddBuffer(const std::shared_ptr<Buffer>& buffer,
	const std::shared_ptr<Shader>& shader)
{
	if (!shader) m_bufferShaderPairs.push_back(std::make_pair(buffer, State::defaultShader));
	else         m_bufferShaderPairs.push_back(std::make_pair(buffer, shader));
}

void Mesh::AddBuffer(const std::shared_ptr<Buffer>& buffer, const Material& material)
{
    // No storing shaders directly, only a material per buffer
    m_bufferMatPairs.push_back(std::make_pair(buffer, material));
}

size_t Mesh::GetNumBuffers() const
{
	return m_bufferShaderPairs.size();
}

const std::shared_ptr<Buffer>& Mesh::GetBuffer(size_t index) const
{
	return m_bufferShaderPairs.at(index).first;
}

std::shared_ptr<Buffer>& Mesh::GetBuffer(size_t index)
{
	return m_bufferShaderPairs.at(index).first;
}

const Material& Mesh::GetMaterial(size_t index) const
{
    return m_bufferMatPairs.at(index).second;
}

Material& Mesh::GetMaterial(size_t index)
{
    return m_bufferMatPairs.at(index).second;
}

void Mesh::Draw()
{
    for (auto& pair : m_bufferMatPairs)
    {
        // Prepare material
        pair.second.Prepare();
        // Draw buffer with material's shader
        pair.first->Draw(*pair.second.GetShader());
    }
}
