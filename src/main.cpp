#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "common.h"
#include "buffer.h"
#include "camera.h"
#include "mesh.h"
#include "material.h"
#include "model.h"
#include "shader.h"
#include "state.h"
#include "texture.h"
#include "utils.h"
#include "vertex.h"
#include "world.h"

#include "../lib/glfw/glfw3.h"
#include <fstream>
#include <iostream>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using std::cout;
using std::endl;

int main()
{
    // Init GLFW
    if ( !glfwInit() ) {
        std::cout << "could not initialize glfw" << std::endl;
        return -1;
    }
    // Create window
    glfwWindowHint(GLFW_SAMPLES, 8);
    GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
	if (!win)
    {
        cout << "Could not create OpenGL window." << endl;
        glfwTerminate();
        return -1;
    }
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(win);
    // Prepare Window & OpenGL extensions
    if (!Init())
    {
        cout << "Could not initialize Engine." << endl;
        return -1;
    }

    // Load default shader
    ShaderPtr shader = Shader::Create(readString("data/vertex.glsl"),
        readString("data/fragment.glsl"));
    if (!shader)
    {
        cout << "Error: Could not create shaders" << endl;
        cout << Shader::GetError() << endl;
        return -1;
    }	
    State::defaultShader = shader;
    
    // World
    WorldPtr world = World::Create();
	// Camera
    CameraPtr camera = Camera::Create();
    camera->SetPosition(glm::vec3(0.f, 0.01f, 0.f));
    camera->SetClearColor(glm::vec3(0.f, 1.f, 1.f));
	world->AddEntity(camera);
	
	// Mesh
    MeshPtr meshTown = Mesh::Load("data/asian_town.msh.xml");
    ModelPtr town = Model::Create(meshTown);
    world->AddEntity(town);

	// Camera control local vars =============================
	float cameraSpeed = 0.05f;
	int   speedMX, speedMY;
	int   lastMX = 0;
	int   lastMY = 0;
	// =======================================================

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
        camera->SetViewport(glm::ivec4(0, 0, screenWidth, screenHeight));

        // Projection matrix
        float fovy   = glm::radians(45.f);
        float aspect = static_cast<float>(screenWidth) / screenHeight;
        float near   = 0.001f;
        float far    = 100.f;
        glm::mat4 projection = glm::perspective(fovy, aspect, near, far);
        camera->SetProjection(projection);

        // Update
        world->Update(deltaTime);
        
		// Camera rotation
		double mouseX, mouseY;
		glfwGetCursorPos(win, &mouseX, &mouseY);
		speedMX = static_cast<int>(mouseX - lastMX);
		speedMY = static_cast<int>(mouseY - lastMY);
		lastMX = mouseX;
		lastMY = mouseY;
		float cameraRotateSpeed = 5.f;
		camera->AddYaw  (-speedMX * cameraRotateSpeed * deltaTime);
		camera->AddPitch(-speedMY * cameraRotateSpeed * deltaTime);
		
		// Camera movement
		if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera->Move(glm::vec3(0, 0, -cameraSpeed * deltaTime));
		}
		else if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera->Move(glm::vec3(0, 0, cameraSpeed * deltaTime));
		}
		else if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera->Move(glm::vec3(cameraSpeed * deltaTime, 0, 0));
		}
		else if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera->Move(glm::vec3(-cameraSpeed * deltaTime, 0, 0));
		}


        // Draw
        world->Draw();

        // Refresh screen
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
}
