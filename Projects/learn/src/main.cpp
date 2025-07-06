// To run: cd src > 
// g++ -g -std=c++17 -I../include -L../lib glad.c Window.cpp main.cpp Mesh.cpp Shader.cpp Camera.cpp -lglfw3dll -lopengl32 -o ../build/run.exe && ../build/run.exe


#define STB_IMAGE_IMPLEMENTATION
#include "../include/config.h"
#include <iostream>

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList; 
std::vector<Shader> shaderList;
Camera camera;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

void CreateObjects()
{
    unsigned int indices[] = {
        0, 2, 5
        // 0, 3, 1,
        // 1, 3, 2,
        // 2, 3, 0,
        // 0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, // left bottom (0)
        0.0f, -1.0f, 1.0f,  // bottom front center
        1.0f, -1.0f, 0.0f,  // right bottom
        0.0f, 1.0f, 0.0f,    // up back center (3)
        1.0f, 1.0f, 0.0f,   // top right
        -1.0f, 1.0f, 0.0f   // top left (5)
    };

    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    Mesh* obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj2);
}

void CreateShaders()
{
    Shader shader1;
    
    // Embedded vertex shader
    const char* vertexCode = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        uniform mat4 model;
        uniform mat4 projection;
        uniform mat4 view;

        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
    )glsl";
    
    // Embedded fragment shader
    const char* fragmentCode = R"glsl(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(0.8, 0.3, 0.2, 1.0);
        }
    )glsl";
    
    shader1.CreateFromString(vertexCode, fragmentCode);
    shaderList.push_back(shader1);
}

int main()
{
    
    mainWindow = Window(800, 600);
    mainWindow.Initialise();
    
    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    CreateObjects();
    CreateShaders();

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), 
                   glm::vec3(0.0f, 1.0f, 0.0f), 
                   -90.0f, 0.0f, 5.0f, 0.5f);

    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), 
        (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 
        0.1f, 
        100.0f
    );

    // Loop until window closed
    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        // Get + Handle User Input
        glfwPollEvents();

        camera.keyControl(mainWindow.getsKeys(), deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        // Clear the window
        glClearColor(0.4f, 0.6f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();

        glm::mat4 model(1.0f);

        // First object
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        meshList[0]->RenderMesh();

        //Second object
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshList[1]->RenderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    // Clean up mesh objects
    for (auto* mesh : meshList) {
        delete mesh;
    }

    return 0;
}