#include "../header/Window.h"

Window::Window() {
    width = 800;
    height = 600;

    for (int i = 0; i < 1024; i++) {
        keys[i] = false;
    }

    xChange = 0.0f;
    yChange = 0.0f;

    mouseFirstMoved = true;
}

Window::Window(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;

    for (int i = 0; i < 1024; i++) {
        keys[i] = false;
    }

    xChange = 0.0f;
    yChange = 0.0f;

    mouseFirstMoved = true;
}

int Window::Initialise() {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("GLFW initialization failed!\n");
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac compatibility

    // Create window
    mainWindow = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);
    if (!mainWindow) {
        printf("GLFW window creation failed!\n");
        glfwTerminate();
        return 1;
    }

    // Get buffer size info
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Make context current
    glfwMakeContextCurrent(mainWindow);

    // Handle user input
    createCallbacks();
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Load OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return 1;
    }

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    return 0;
}

void Window::createCallbacks() {
    glfwSetWindowUserPointer(mainWindow, this);
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Window::getXChange() {
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
}

GLfloat Window::getYChange() {
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            theWindow->keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            theWindow->keys[key] = false;
        }
    }
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) {
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (theWindow->mouseFirstMoved) { // if true
        theWindow->lastX = static_cast<GLfloat>(xPos);
        theWindow->lastY = static_cast<GLfloat>(yPos);
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = static_cast<GLfloat>(xPos) - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - static_cast<GLfloat>(yPos);

    theWindow->lastX = static_cast<GLfloat>(xPos);
    theWindow->lastY = static_cast<GLfloat>(yPos);
}

// Triggered automatically when the program finishes execution (end of the main function)
Window::~Window() { 
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
