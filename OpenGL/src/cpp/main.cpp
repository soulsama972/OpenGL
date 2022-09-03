#include"window.h"

// test case
#include"tests/testMenu.h"
#include"tests/testTextrue.h"
#include"tests/testDrawSqure.h"
#include"tests/testDrawModel.h"
#include"tests/testClearColor.h"

Window window;
int main(void)
{
    window.Init(1920, 1080, "title");
    Renderer renderer;
    Test* currentTest = nullptr;
    TestMenu menu(currentTest);
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));
    menu.RegisterTest<TestClearColor>("clearColor");
    menu.RegisterTest<TestDrawSqure>("DrawSqure");
    menu.RegisterTest<TestTextrue2D>("testDrawTextrue");
    menu.RegisterTest<TestDrawModel>("testDrawModel");
    currentTest = &menu;
    currentTest = new TestDrawModel();
    //window.HideCursor();
    //window.ShowCurosr();

    while (!window.IsDestoryed())
    {
        window.timer.Tick();
        renderer.Clear(0,0.5,0.5,0.5);
        currentTest->ImGuiBegin();

        if (currentTest)
        {
            currentTest->OnUpdate(window.timer.GetDeltaTime());
            currentTest->OnRender();
            currentTest->OnImGuiRender();
        }

        menu.ExitToMenu();
        currentTest->ImGuiEnd();

        window.Present();

    }
    return 0;
}