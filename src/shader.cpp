#include "shader.h"
#include "../lib/glfw/glfw3.h"
#include <iostream>

ShaderPtr Shader::Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	// Shared pointer constructor (make_shared needs public constructor/destructor)
	std::shared_ptr<Shader> shaderPtr(new Shader(vertexShaderSource, fragmentShaderSource), 
		[](Shader* p) { delete p; }); // Custom destructor lambda

	if (shaderPtr->GetId == 0) return nullptr;
	else return shaderPtr;
}

Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	// Create vertex shader
	int retCode;
	const char* cVertexShaderSource = vertexShaderSource.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &cVertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE)
	{
		glGetShaderInfoLog(vertexShader, sizeof(errorLog), nullptr, errorLog);
		std::cout << "Error: Vertex shader could not be compiled:" << std::endl << errorLog << std::endl;
		glDeleteShader(vertexShader);
		glfwTerminate();
		return;
	}

	// Create fragment shader
	const char* cFragmentShaderSource = fragmentShaderSource.c_str();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &cFragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(errorLog), nullptr, errorLog);
		std::cout << "Error: Fragment shader could not be compiled:" << std::endl << errorLog << std::endl;
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glfwTerminate();
		return;
	}

	// Create and link program
	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glGetProgramiv(id, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE)
	{
		glGetProgramInfoLog(id, sizeof(errorLog), nullptr, errorLog);
		std::cout << "Error: Program could not be linked:" << std::endl << errorLog << std::endl;
		glDeleteProgram(id);
		glfwTerminate();
		return;
	}

	// Get and store attribute vars of shaders
	// ...
}

Shader::~Shader()
{
	// Release data in VRAM
	// ...
}

// Activa el uso de este programa
void Shader::Use() const
{
	//...
}

// Activa la escritura de las variables attribute, y especifica su formato
void Shader::SetupAttribs() const
{
	//...
}

// Obtiene la localización de una variable uniform
int Shader::GetLocation(const char* name) const
{
	return 0;
}

// Da valor a una variable uniform
void Shader::SetInt(int loc, int val)
{

}

void Shader::SetFloat(int loc, float val)
{

}

void Shader::SetVec3(int loc, const glm::vec3& vec)
{

}

void Shader::SetVec4(int loc, const glm::vec4& vec)
{

}

void Shader::SetMatrix(int loc, const glm::mat4& matrix)
{

}

