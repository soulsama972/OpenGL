#include "window.h"

extern void InputCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
extern void ScrollCallBack(GLFWwindow* window, double xOffset, double yOffset);
extern void MouseInsideCallBack(GLFWwindow* window, int entered);
extern void MouseMoveCallBack(GLFWwindow* window, double xOffset, double yOffset);
extern void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);

Window::Window():screenHeight(0),screenWidth(0),window(0)
{
}

Window::Window(uint screenWidth, uint screenHeight, const std::string& title):
screenHeight(screenHeight), screenWidth(screenWidth),window(0)
{
    Init(screenHeight, screenHeight, title);
}

Window::~Window()
{
    glfwTerminate();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void Window::Init(uint screenWidth, uint screenHeight, const std::string& title)
{
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1920, 1080, title.c_str(), NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(window);
    
    if (GLEW_OK != glewInit())
    {
        std::cout << "could not glfwMakeContextCurrent" << std::endl;
        return;
    }
    

    // set all callbacks
// keyboard
    GLCall(glfwSetKeyCallback(window, InputCallBack));
    // cursor
    GLCall(glfwSetCursorEnterCallback(window, MouseInsideCallBack));
    GLCall(glfwSetScrollCallback(window, ScrollCallBack));
    GLCall(glfwSetCursorPosCallback(window, MouseMoveCallBack));
    GLCall(glfwSetMouseButtonCallback(window, MouseButtonCallBack));

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();



}

void Window::SetTitle(const std::string& title) const
{
    GLCall(glfwSetWindowTitle(window, title.c_str()));
}

void Window::HideCursor() const
{
    GLCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
}

void Window::ShowCurosr() const
{
    GLCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));
}

bool Window::IsDestoryed() const
{
    return glfwWindowShouldClose(window);
}

void Window::Present() const
{

    glfwSwapBuffers(window);
    glfwPollEvents();
}




