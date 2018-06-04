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
    ShaderPtr shader = Shader::Create(readString("data/vertex.glsl"), readString("data/fragment.glsl"));
    if (!shader)
    {
        cout << "Error: Could not create shaders" << endl;
        cout << Shader::GetError() << endl;
        return -1;
    }	
    State::defaultShader = shader;
    
    // World
    World world;
    CameraPtr camera = Camera::Create();
    world.AddEntity(camera);
    camera->SetPosition(glm::vec3(0.f, 1.f, 3.f));
    camera->SetRotation(glm::vec3(glm::radians(-20.f), 0.f, 0.f));
    camera->SetClearColor(glm::vec3(0.1f, 0.1f, 0.1f));

    // Load buffer with a square
    std::vector<Vertex> vertexs{
		Vertex(glm::vec3( .5f,  .5f, 0)),
        Vertex(glm::vec3(-.5f,  .5f, 0)),
        Vertex(glm::vec3(-.5f, -.5f, 0)),
        Vertex(glm::vec3( .5f, -.5f, 0))
    };
	vertexs[0].tex = glm::vec2(1.f, 1.f);
	vertexs[1].tex = glm::vec2(0.f, 1.f);
	vertexs[2].tex = glm::vec2(0.f, 0.f);
	vertexs[3].tex = glm::vec2(1.f, 0.f);

    std::vector<uint16_t> indexes { 0, 1, 2, 0, 2, 3 };
    BufferPtr buffer = Buffer::Create(vertexs, indexes);
    
    // Load textures
    TexturePtr textureFront = Texture::Load("data/front.png");
    TexturePtr textureTop   = Texture::Load("data/top.png");
    Material mat(textureFront);
    
	// Square mesh
    MeshPtr mesh = Mesh::Create();
    mesh->AddBuffer(buffer, mat);
    ModelPtr model = Model::Create(mesh);
    world.AddEntity(model);

    float rotationSpeed = 32.f;
    float currentAngle = 0.f;

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
        world.Update(deltaTime);
        currentAngle += deltaTime * rotationSpeed;        
		model->SetRotation(glm::vec3(0.f, glm::radians(currentAngle), 0.f));        
        
        // Draw
        world.Draw();

        // Refresh screen
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
}
