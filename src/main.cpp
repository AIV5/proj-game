#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaderloader.h"
#include "settings.h"
#include "render.h"

extern GLFWwindow* window;
extern GLuint VAO, prog;


void init (void) {
    /* Initialize the library */
    if (!glfwInit())
        exit(-1);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(PGS_START_WINDOW_WIDTH, PGS_START_WINDOW_HEIGHT, "Projective Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    if (!gladLoadGL()) {
        std::cout << "Can't load glad\n";
        exit(-1);
    }

    std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << '\n';

    glfwSetWindowSizeCallback(window, changeSize);

    prog = loadProgram();
    glUseProgram(prog);
    sendResolution();
    renderLoad();
}

void loop (void) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    renderLoop();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

int main(void)
{
    init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        loop();
    }

    glfwTerminate();
    return 0;
}
