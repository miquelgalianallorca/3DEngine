#pragma once

#include "common.h"

class Shader;
typedef std::shared_ptr<Shader> ShaderPtr;

class Shader
{
public:	
	static ShaderPtr Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	
	// Devuelve el identificador de OpenGL del programa
	uint32_t GetId() const { return m_id; }

	// Obtiene el mensaje de error generado al compilar o enlazar
	// Estático para guardar el error del ultimo shader que se ha producido.
	static const std::string& GetError() { return m_errorLog; }

	// Activa el uso de este programa
	void Use() const;

	// Activa la escritura de las variables attribute, y especifica su formato
	void SetupAttribs() const;

	// Obtiene la localización de una variable uniform
	int	GetLocation(const std::string& name) const;

	// Da valor a una variable uniform
	// Estaticos porque el valor del location sera el mismo, sea el
	// shader que sea.
	static void SetInt   (int loc, int val);
	static void SetFloat (int loc, float val);
	static void SetVec3  (int loc, const glm::vec3& vec);
	static void SetVec4  (int loc, const glm::vec4& vec);
	static void SetMatrix(int loc, const glm::mat4& matrix);
	
private:
	Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	~Shader();

	uint32_t m_id;
	static std::string m_errorLog;

	uint32_t vertexShader, fragmentShader;
    
    // Attribute vars location
	int32_t m_vPosLoc, m_vTexLoc;
};