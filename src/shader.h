#pragma once

#include "common.h"

class Shader;
typedef std::shared_ptr<Shader> ShaderPtr;

class Shader
{
public:
	
	static ShaderPtr Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	
	// Devuelve el identificador de OpenGL del programa
	uint32_t GetId() const { return id; }

	// Obtiene el mensaje de error generado al compilar o enlazar
	const char*	GetError() const { return errorLog; }

	// Activa el uso de este programa
	void Use() const;

	// Activa la escritura de las variables attribute, y especifica su formato
	void SetupAttribs() const;

	// Obtiene la localización de una variable uniform
	int	GetLocation(const char* name) const;

	// Da valor a una variable uniform
	void SetInt   (int loc, int val);
	void SetFloat (int loc, float val);
	void SetVec3  (int loc, const glm::vec3& vec);
	void SetVec4  (int loc, const glm::vec4& vec);
	void SetMatrix(int loc, const glm::mat4& matrix);
	
private:
	Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	~Shader();

	uint32_t id;
	char errorLog[1024];

	uint32_t vertexShader, fragmentShader;
	int32_t vPosLoc; //, vColorLoc;
};