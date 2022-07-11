#include<iostream>

// gl
#include<GL/glew.h>
#include<GLFW/glfw3.h>

// renderer
#include"shader.h"
#include"textrue.h"
#include"renderer.h"
#include"vertexArray.h"
#include"indexBuffer.h"
#include"vertexBuffer.h"
#include"vertexBufferLayout.h"

// math
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

// imgui
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1600, 900, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));
    if (GLEW_OK != glewInit())
        std::cout << "error" << std::endl;
    
    {
        /* Loop until the user closes the window */
        float positions[] = {
            -50.f, -50.0f, 0.0f, 0.0f, // 0
             50.f, -50.0f, 1.0f, 0.0f, // 1
             50.f,  50.0f, 1.0f, 1.0f, // 2
            -50.f,  50.0f, 0.0f, 1.0f, // 3
        };
        uint indices[] = {
            0,1,2
           ,2,3,0
        };
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
        ImGui::StyleColorsDark();

        Renderer renderer;
        VertexArray va;
        VertexBufferLayout layout;
        Shader shader("res/shaders/basic.shader");
        Textrue texture("res/textures/goku.png");
        VertexBuffer vb(positions, sizeof(float) * 4 * 4);
        IndexBuffer ib(indices, 6);
        glm::mat4 model, view, proj;

        proj = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);
        view = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));

        renderer.PrintGLVersion();
        
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
  
        texture.Bind();
        shader.Bind();
        shader.SetUniform1i("u_Tex", 0);

        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        glm::vec3 t(200, 200, 0);
        glm::vec3 t2(400, 200, 0);

        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("debug");
            ImGui::SliderFloat2("translationA", &t.x, 0.0f, 1600.0f);
            ImGui::SliderFloat2("translationB", &t2.x, 0.0f, 1600.0f);
            ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
            ImGui::End();

            model = glm::translate(glm::mat4(1), t);
            glm::mat4 mvp = proj * view * model;
        
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);

            model = glm::translate(glm::mat4(1), t2);
            mvp = proj * view * model;
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}