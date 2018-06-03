#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "common.h"
#include "buffer.h"
#include "camera.h"
#include "mesh.h"
#include "model.h"
#include "shader.h"
#include "state.h"
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

    // Load shaders
    ShaderPtr shader = Shader::Create(readString("../data/vertex.glsl"), readString("../data/fragment.glsl"));
    if (!shader)
    {
        cout << "Error: Could not create shaders" << endl;
        cout << Shader::GetError() << endl;
        return -1;
    }	
    shader->Use(); // delete this
    State::defaultShader = shader;
    int mvpLoc = shader->GetLocation("MVP"); // delete this

    // World
    World world;
    CameraPtr camera = Camera::Create();
    world.AddEntity(camera);
    camera->SetPosition(glm::vec3(0.f, 0.f, 6.f));
    camera->SetClearColor(glm::vec3(0.1f, 0.1f, 0.1f));

    // Load buffer with a triangle
    std::vector<Vertex> vertices{
        Vertex(glm::vec3(   0,  .5f, 0)),
        Vertex(glm::vec3(-.5f, -.5f, 0)),
        Vertex(glm::vec3( .5f, -.5f, 0))
    };
    std::vector<uint16_t> indexes { 0, 1, 2 };
    BufferPtr buffer = Buffer::Create(vertices, indexes);

    MeshPtr mesh = Mesh::Create();
    mesh->AddBuffer(buffer);
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

        // Update logic
        currentAngle += deltaTime * rotationSpeed;

        // Projection matrix
        float fovy   = glm::radians(45.f);
        float aspect = static_cast<float>(screenWidth) / screenHeight;
        float near   = 0.1f;
        float far    = 100.f;
        glm::mat4 projection = glm::perspective(fovy, aspect, near, far);
        camera->SetProjection(projection);

        world.Update(deltaTime);
        world.Draw();

        // Draw triangles
        //for (size_t i = 0; i < 9; ++i)
        //{
        //    // Positioning
        //    int row = i / 3;
        //    int col = i % 3;
        //    glm::vec3 translation(3 - 3 * row, 0, -3 * col);

        //    // MVP matrix
        //    glm::mat4 model = glm::translate(glm::mat4(), translation) * 
        //        glm::rotate(glm::mat4(), glm::radians(currentAngle), glm::vec3(0, 1, 0)) * 
        //        glm::scale(glm::mat4(), glm::vec3(1, 1, 1));

        //    glm::mat4 MVP = projection * view * model;
        //    Shader::SetMatrix(mvpLoc, MVP);

        //    // Draw
        //    buffer->Draw(*shader);
        //}

        // Refresh screen
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
}
