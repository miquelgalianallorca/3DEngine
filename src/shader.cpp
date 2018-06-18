#include "shader.h"
#include "state.h"
#include "vertex.h"
#include <iostream>

using std::cout;
using std::endl;

std::string Shader::m_errorLog;

ShaderPtr Shader::Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	// Reset error message static var
	m_errorLog = "";

	// Shared pointer constructor (make_shared needs public constructor/destructor)
	// with custom destructor lambda
	std::shared_ptr<Shader> shaderPtr(new Shader(vertexShaderSource, fragmentShaderSource),
		[](Shader* p) { delete p; }); 

	if (shaderPtr->GetId() == 0) return nullptr;
	else return shaderPtr;
}

Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) :
	m_id(0)
{
	// Create vertex shader
	int retCode;
	char errorLog[1024];
	const char* cVertexShaderSource = vertexShaderSource.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &cVertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE)
	{
		glGetShaderInfoLog(vertexShader, sizeof(errorLog), nullptr, errorLog);
		m_errorLog = errorLog;
		glDeleteShader(vertexShader);
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
		m_errorLog = errorLog;
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return;
	}

	// Create and link program
	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glGetProgramiv(m_id, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE)
	{
		glGetProgramInfoLog(m_id, sizeof(errorLog), nullptr, errorLog);
		m_errorLog = errorLog;
		glDeleteProgram(m_id);
		return;
	}

	// Get and store attribute vars of shaders
	m_vPosLoc    = glGetAttribLocation(m_id, "vpos");
	m_vTexLoc    = glGetAttribLocation(m_id, "vtex");
	m_vNormalLoc = glGetAttribLocation(m_id, "vnormal");
}

Shader::~Shader()
{
	// Release data in VRAM
	if (m_id) glDeleteProgram(m_id);
}

// Activa el uso de este programa
void Shader::Use() const
{
	glUseProgram(m_id);
}

// Activa la escritura de las variables attribute, y especifica su formato
void Shader::SetupAttribs() const
{
    // Vertex location
	if (m_vPosLoc != -1)
	{
		glEnableVertexAttribArray(m_vPosLoc);
		glVertexAttribPointer(m_vPosLoc, 3, GL_FLOAT, false, sizeof(Vertex),
			reinterpret_cast<const void*>(offsetof(Vertex, pos)));
	}
    // Vertex texture coord.
    if (m_vTexLoc != -1)
    {
        glEnableVertexAttribArray(m_vTexLoc);
        glVertexAttribPointer(m_vTexLoc, 2, GL_FLOAT, false, sizeof(Vertex),
            reinterpret_cast<const void*>(offsetof(Vertex, tex)));
    }
	// Vertex normals
	if (m_vNormalLoc != -1)
	{
		glEnableVertexAttribArray(m_vNormalLoc);
		glVertexAttribPointer(m_vNormalLoc, 3, GL_FLOAT, false, sizeof(Vertex),
			reinterpret_cast<const void*>(offsetof(Vertex, normal)));
	}
}

// Get location of uniform var
int Shader::GetLocation(const std::string& name) const
{
	return glGetUniformLocation(m_id, name.c_str());
}

// Set uniform var
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
	glUniform3fv(loc, 1, glm::value_ptr(vec));
}

void Shader::SetVec4(int loc, const glm::vec4& vec)
{
	if (loc == -1)
	{
		cout << "Invalid location in Shader::SetVec4" << endl;
		return;
	}
	glUniform4fv(loc, 1, glm::value_ptr(vec));
}

void Shader::SetMatrix(int loc, const glm::mat4& matrix)
{
	if (loc == -1)
	{
		cout << "Invalid location in Shader::SetMatrix" << endl;
		return;
	}
	glUniformMatrix4fv(loc, 1, false, value_ptr(matrix));
}
