#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "buffer.h"
#include "common.h"
#include "shader.h"
#include "utils.h"
#include "vertex.h"

#include "../lib/glfw/glfw3.h"
#include <fstream>
#include <iostream>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using std::cout;
using std::endl;

//struct Vertex {
//	float x, y;
//	float r, g, b;
//
//	Vertex(float x, float y, float r, float g, float b)
//	:
//		x(x), y(y),
//		r(r), g(g), b(b)
//	{}
//};


//
//int main2() {
//	// Init glfw
//	if (!glfwInit()) {
//		std::cout << "Could not initialize glfw" << std::endl;
//		return -1;
//	}
//
//	// Create window
//	//glfwWindowHint(GLFW_RESIZABLE, false);
//	glfwWindowHint(GLFW_SAMPLES, 8);
//	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
//	if (!win) {
//		std::cout << "Could not create opengl window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(win);
//
//	// Initialize opengl extensions
//	if (glewInit() != GLEW_OK) {
//		std::cout << "Could not initialize opengl extensions" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	// Load shader's code
//	std::string vertexShaderSource = readString("data/vertex.glsl");
//	std::string fragmentShaderSource = readString("data/fragment.glsl");
//
//	// Create vertex shader
//	int retCode;
//	const char* cVertexShaderSource = vertexShaderSource.c_str();
//	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &cVertexShaderSource, nullptr);
//	glCompileShader(vertexShader);
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &retCode);
//	if (retCode == GL_FALSE) {
//		char errorLog[1024];
//		glGetShaderInfoLog(vertexShader, sizeof(errorLog), nullptr, errorLog);
//		std::cout << "Error: Vertex shader could not be compiled:" << std::endl << errorLog << std::endl;
//		glDeleteShader(vertexShader);
//		glfwTerminate();
//		return -1;
//	}
//
//	// Create fragment shader
//	const char* cFragmentShaderSource = fragmentShaderSource.c_str();
//	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &cFragmentShaderSource, nullptr);
//	glCompileShader(fragmentShader);
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &retCode);
//	if (retCode == GL_FALSE) {
//		char errorLog[1024];
//		glGetShaderInfoLog(fragmentShader, sizeof(errorLog), nullptr, errorLog);
//		std::cout << "Error: Fragment shader could not be compiled:" << std::endl << errorLog << std::endl;
//		glDeleteShader(vertexShader);
//		glDeleteShader(fragmentShader);
//		glfwTerminate();
//		return -1;
//	}
//
//	// Create and link program
//	uint32_t program = glCreateProgram();
//	glAttachShader(program, vertexShader);
//	glAttachShader(program, fragmentShader);
//	glLinkProgram(program);
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//	glGetProgramiv(program, GL_LINK_STATUS, &retCode);
//	if (retCode == GL_FALSE) {
//		char errorLog[1024];
//		glGetProgramInfoLog(program, sizeof(errorLog), nullptr, errorLog);
//		std::cout << "Error: Program could not be linked:" << std::endl << errorLog << std::endl;
//		glDeleteProgram(program);
//		glfwTerminate();
//		return -1;
//	}
//
//	// use program and get locations
//	int vposLoc = glGetAttribLocation(program, "vpos");
//	int vcolorLoc = glGetAttribLocation(program, "vcolor");
//	glUseProgram(program);
//
//	// initialize opengl states
//	glEnable(GL_SCISSOR_TEST);
//	//glEnableClientState(GL_VERTEX_ARRAY); // ***
//	//glEnableClientState(GL_COLOR_ARRAY); // ***
//	glEnableVertexAttribArray(vposLoc);
//	glEnableVertexAttribArray(vcolorLoc);
//
//	// define triangle
//	std::vector<Vertex> vertices = {
//		Vertex( 0,  1,  1, 0, 0),
//		Vertex(-1, -1,  0, 1, 0),
//		Vertex( 1, -1,  0, 0, 1)
//	};
//
//	// store triangle in vram
//	uint32_t vertexBuffer;
//	glGenBuffers(1, &vertexBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
//
//	// describe data for vertex buffer objects
//	//glVertexPointer(2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, x))); // ***
//	//glColorPointer(3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, r))); // ***
//	glVertexAttribPointer(vposLoc, 2, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, x)));
//	glVertexAttribPointer(vcolorLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, r)));
//
//	// describe data for vertex arrays
//	//glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &vertices[0].x); // ***
//	//glColorPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].r); // ***
//
//	// Main loop
//	double lastTime = glfwGetTime();
//	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
//		// Get delta time
//		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
//		lastTime = glfwGetTime();
//
//		// Get window size
//		int screenWidth, screenHeight;
//		glfwGetWindowSize(win, &screenWidth, &screenHeight);
//
//		// Setup viewport
//		glViewport(0, 0, screenWidth, screenHeight);
//		glScissor(0, 0, screenWidth, screenHeight);
//
//		// Clear screen
//		glClearColor(0, 0, 0, 1);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// Draw with vertex arrays & vbos
//		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
//		
//		// Draw with glBegin ... glEnd
//		/*glBegin(GL_TRIANGLES);
//			glColor4f(1, 0, 0, 1);
//			glVertex2f(0, 1);
//			glColor4f(0, 1, 0, 1);
//			glVertex2f(-1, -1);
//			glColor4f(0, 0, 1, 1);
//			glVertex2f(1, -1);
//		glEnd();*/
//
//		// Refresh screen
//		glfwSwapBuffers(win);
//		glfwPollEvents();
//	}
//
//	// Shutdown
//	glDeleteProgram(program);
//	glDeleteBuffers(1, &vertexBuffer);
//	glfwTerminate();
//
//	return 0;
//}


GLFWwindow* win = nullptr;

bool Init()
{
	// Init glfw
	if (!glfwInit())
	{
		std::cout << "Could not initialize glfw" << std::endl;
		return false;
	}

	// Create window
	glfwWindowHint(GLFW_SAMPLES, 8);
	win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
	if (!win)
	{
		std::cout << "Could not create opengl window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(win);

	// Initialize opengl extensions
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Could not initialize opengl extensions" << std::endl;
		glfwTerminate();
		return false;
	}

	// Enable OpenGL states
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	return true;
}

int main()
{
	// Prepare Window & OpenGL extensions
	if (!Init()) return -1;
	
	// Load shaders
	std::string vertexShaderSource   = readString("data/vertex.glsl");
	std::string fragmentShaderSource = readString("data/fragment.glsl");
	ShaderPtr shader = Shader::Create(vertexShaderSource, fragmentShaderSource);
	if (!shader)
	{
		cout << "Error: Could not create shaders" << endl;
		return -1;
	}
	
	shader->Use();

	// Load buffer with a triangle
	std::vector<Vertex> vertices{
		Vertex(-1, 0, -10),
		Vertex( 0, 1, -10),
		Vertex( 1, 0, -10)
	};
	std::vector<uint16_t> indexes { 0, 1, 2 };
	Buffer buffer(vertices, indexes);
	
	float rotationSpeed = 32.f;

	// Main loop
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE))
	{
		// Update delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();
		
		// Setup viewport
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);
		glViewport(0, 0, screenWidth, screenHeight);
		glScissor (0, 0, screenWidth, screenHeight);
		
		// Clear screen
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Calculate Model-View-Projection matrix
		float fovy   = glm::radians(60.f);
		float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
		float near   = 0.1f;
		float far    = 100.f;
		glm::mat4 projection = glm::perspective(fovy, aspect, near, far);

		glm::vec3 eye    = { 0.f, 0.f, 0.6f };
		glm::vec3 center = { 0.f, 0.f, 0.f  };
		glm::vec3 up     = { 0.f, 1.f, 0.f  };
		glm::mat4 modelView = glm::lookAt(eye, center, up);
		glm::mat4 MVP = projection * modelView;
		//model = translate * rotate * scale

		// Set MVP in shader
		int mvpLocation = shader->GetLocation("MVP");
		shader->SetMatrix(mvpLocation, MVP);
				
		// Draw
		shader->Use();
		buffer.Draw(*shader);

		// Refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
}
