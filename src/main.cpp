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
    camera->SetPosition(glm::vec3(0.f, 10.f, 3.f));
    camera->SetRotation(glm::vec3(glm::radians(-40.f), 0.f, 0.f));
    camera->SetClearColor(glm::vec3(0.f, 1.f, 1.f));
	world->AddEntity(camera);

 //   // Vertex buffer objects
 //   std::vector<Vertex> vertexsFront{
	//	// Front
	//	Vertex(glm::vec3( .5f,  .5f, -.5f), glm::vec2(1.f, 1.f)), // 0
 //       Vertex(glm::vec3(-.5f,  .5f, -.5f), glm::vec2(0.f, 1.f)), // 1
 //       Vertex(glm::vec3(-.5f, -.5f, -.5f), glm::vec2(0.f, 0.f)), // 2
 //       Vertex(glm::vec3( .5f, -.5f, -.5f), glm::vec2(1.f, 0.f)), // 3
	//	// Right
	//	Vertex(glm::vec3( .5f,  .5f,  .5f), glm::vec2(1.f, 1.f)), // 4
	//	Vertex(glm::vec3( .5f,  .5f, -.5f), glm::vec2(0.f, 1.f)), // 5
	//	Vertex(glm::vec3( .5f, -.5f, -.5f), glm::vec2(0.f, 0.f)), // 6
	//	Vertex(glm::vec3( .5f, -.5f,  .5f), glm::vec2(1.f, 0.f)), // 7
	//	// Back
	//	Vertex(glm::vec3( .5f,  .5f,  .5f), glm::vec2(0.f, 1.f)), // 8
	//	Vertex(glm::vec3(-.5f,  .5f,  .5f), glm::vec2(1.f, 1.f)), // 9
	//	Vertex(glm::vec3(-.5f, -.5f,  .5f), glm::vec2(1.f, 0.f)), // 10
	//	Vertex(glm::vec3( .5f, -.5f,  .5f), glm::vec2(0.f, 0.f)), // 11
	//	// Left
	//	Vertex(glm::vec3(-.5f,  .5f,  .5f), glm::vec2(0.f, 1.f)), // 12
	//	Vertex(glm::vec3(-.5f,  .5f, -.5f), glm::vec2(1.f, 1.f)), // 13
	//	Vertex(glm::vec3(-.5f, -.5f, -.5f), glm::vec2(1.f, 0.f)), // 14
	//	Vertex(glm::vec3(-.5f, -.5f,  .5f), glm::vec2(0.f, 0.f))  // 15
 //   };
 //   std::vector<uint16_t> indexsFront {
	//	0, 1, 2,
	//	0, 2, 3,
	//	4, 5, 6,
	//	4, 6, 7,
	//	8, 9, 10,
	//	8, 10, 11,
	//	12, 13, 14,
	//	12, 14, 15
	//};
	//
	//std::vector<Vertex> vertexsTop {
	//	// Top
	//	Vertex(glm::vec3( .5f,  .5f,  .5f), glm::vec2(1.f, 1.f)), // 0
	//	Vertex(glm::vec3(-.5f,  .5f,  .5f), glm::vec2(0.f, 1.f)), // 1
	//	Vertex(glm::vec3(-.5f,  .5f, -.5f), glm::vec2(0.f, 0.f)), // 2
	//	Vertex(glm::vec3( .5f,  .5f, -.5f), glm::vec2(1.f, 0.f)), // 3
	//	// Bottom
	//	Vertex(glm::vec3( .5f, -.5f,  .5f), glm::vec2(1.f, 1.f)), // 4
	//	Vertex(glm::vec3(-.5f, -.5f,  .5f), glm::vec2(0.f, 1.f)), // 5
	//	Vertex(glm::vec3(-.5f, -.5f, -.5f), glm::vec2(0.f, 0.f)), // 6
	//	Vertex(glm::vec3( .5f, -.5f, -.5f), glm::vec2(1.f, 0.f))  // 7
	//};
	//std::vector<uint16_t> indexsTop {
	//	0, 1, 2,
	//	0, 2, 3,
	//	4, 5, 6,
	//	4, 6, 7
	//};
 //   
	//BufferPtr bufferFront = Buffer::Create(vertexsFront, indexsFront);
	//BufferPtr bufferTop   = Buffer::Create(vertexsTop,   indexsTop);
 //   
    // Load textures
    /*TexturePtr textureFront = Texture::Load("data/front.png");
    TexturePtr textureTop   = Texture::Load("data/top.png");
    Material matFront(textureFront);
	Material matTop(textureTop);*/

    MeshPtr meshTown = Mesh::Load("data/asian_town.msh.xml");
    
	// Cube mesh
    /*MeshPtr mesh = Mesh::Create();
    mesh->AddBuffer(bufferFront, matFront);
	mesh->AddBuffer(bufferTop, matTop);
    ModelPtr model = Model::Create(mesh);*/
    ModelPtr town = Model::Create(meshTown);
    //world->AddEntity(model);
    world->AddEntity(town);

    float rotationSpeed = 60.f;
    float currentAngle  =  0.f;

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
        float near   = 0.1f;
        float far    = 100.f;
        glm::mat4 projection = glm::perspective(fovy, aspect, near, far);
        camera->SetProjection(projection);

        // Update
        world->Update(deltaTime);
        currentAngle += deltaTime * rotationSpeed;        
		//model->SetRotation(glm::vec3(0.f, glm::radians(currentAngle), 0.f));

        // Draw
        world->Draw();

        // Refresh screen
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
}
