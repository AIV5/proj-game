#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaderloader.h"
#include "settings.h"

int width = PGS_START_WINDOW_WIDTH;
int height = PGS_START_WINDOW_HEIGHT;
GLFWwindow* window;
GLuint VAO;
GLuint prog;

void _draw_load(){
    float point[] = {1,1, 1,-1, -1,-1, -1,1};

    GLuint pointsVBO;
    glGenBuffers(1, &pointsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void _draw_loop () {
    glBindVertexArray(VAO);
    glDrawArrays(GL_QUADS, 0, 4);
}

void sendResolution () {
    GLuint width_loc = glGetUniformLocation(prog, "width");
    GLuint height_loc = glGetUniformLocation(prog, "height");
    glUniform1i(width_loc, width);
    glUniform1i(height_loc, height);
}

void changeSize(GLFWwindow* _, int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	sendResolution();
}

void init (void) {
    /* Initialize the library */
    if (!glfwInit())
        exit(-1);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Projective Game", NULL, NULL);
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
    _draw_load();
}

void loop (void) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    _draw_loop();

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
