#include "window.h"

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
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    GLCall(glfwSetKeyCallback(window, Input::InputCallBack));

}

void Window::SetTitle(const std::string& title) const
{
    GLCall(glfwSetWindowTitle(window, title.c_str()));
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




