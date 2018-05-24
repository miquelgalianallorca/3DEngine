#include "shader.h"
#include "vertex.h"
#include "../lib/glfw/glfw3.h"
#include <iostream>

using std::cout;
using std::endl;

ShaderPtr Shader::Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	// Shared pointer constructor (make_shared needs public constructor/destructor)
	// with custom destructor lambda
	std::shared_ptr<Shader> shaderPtr(new Shader(vertexShaderSource, fragmentShaderSource),
		[](Shader* p) { delete p; }); 

	if (shaderPtr->GetId() == 0) return nullptr;
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
		cout << "Error: Vertex shader could not be compiled:" << endl << errorLog << endl;
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
		cout << "Error: Fragment shader could not be compiled:" << endl << errorLog << endl;
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
		cout << "Error: Program could not be linked:" << endl << errorLog << endl;
		glDeleteProgram(id);
		glfwTerminate();
		return;
	}

	// Get and store attribute vars of shaders
	vPosLoc   = glGetAttribLocation(id, "vpos");
	vColorLoc = glGetAttribLocation(id, "vcolor");
}

Shader::~Shader()
{
	// Release data in VRAM
	glDeleteProgram(id);

	//glDeleteBuffers(1, &vertexBuffer);
	glfwTerminate();
}

// Activa el uso de este programa
void Shader::Use() const
{
	glUseProgram(id);
}

// Activa la escritura de las variables attribute, y especifica su formato
void Shader::SetupAttribs() const
{
	if (vPosLoc != -1)
	{
		glEnableVertexAttribArray(vPosLoc);

		// Will change when more is added to Vertex
		size_t offsetStride = 0;
		//reinterpret_cast<const void*>(offsetof(Vertex, x))
		glVertexAttribPointer(vPosLoc, 3, GL_FLOAT, false, sizeof(Vertex), &offsetStride);
	}
	//if (vColorLoc != -1)
	//{
	//	glEnableVertexAttribArray(vColorLoc);
	//	
	//	size_t offsetStride = 0;
	//	//reinterpret_cast<const void*>(offsetof(Vertex, r))
	//	glVertexAttribPointer(vColorLoc, 3, GL_FLOAT, false, sizeof(Vertex), &offsetStride);
	//}
}

// Obtiene la localización de una variable uniform
int Shader::GetLocation(const char* name) const
{
	return glGetAttribLocation(id, name);
}

// Da valor a una variable uniform
void Shader::SetInt(int loc, int val)
{
	if (loc == -1)
	{
		cout << "Invalid location in Shader::SetInt" << endl;
		return;
	}

	glUniform1i(loc, val);
}

void Shader::SetFloat(int loc, float val)
{
	if (loc == -1)
	{
		cout << "Invalid location in Shader::SetFloat" << endl;
		return;
	}

	glUniform1f(loc, val);
}

void Shader::SetVec3(int loc, const glm::vec3& vec)
{
	if (loc == -1)
	{
		cout << "Invalid location in Shader::SetVec3" << endl;
		return;
	}

	glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::SetVec4(int loc, const glm::vec4& vec)
{
	if (loc == -1)
	{
		cout << "Invalid location in Shader::SetVec4" << endl;
		return;
	}

	glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetMatrix(int loc, const glm::mat4& matrix)
{
	if (loc == -1)
	{
		cout << "Invalid location in Shader::SetMatrix" << endl;
		return;
	}
	
	glUniformMatrix4fv(loc, 16, false, value_ptr(matrix));
}
