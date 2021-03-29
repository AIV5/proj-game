#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "render.h"
#include "shaderManager.h"

extern GLFWwindow* window;
using glm::vec3, glm::vec4, glm::mat4;

mat4 player = mat4(1);


void init (void) {
    renderLoad();   // this must be the first, I think
    setPlayer(player);
    Figure dot = Figure(vec3(1, 0, 1), vec4(0, 0, 0.1, 1));
    regFig(dot);
    Figure red_line = Figure(vec3(1, 0, 0), vec4(0, 0, 0.3, 1), vec4(0, 1, 0.1, 0));
    regFig(red_line);
    Figure green_line = Figure(vec3(0, 1, 0), vec4(0.1, 0, 0.3, .5), vec4(0, .1, 0.4, 1));
    regFig(green_line);
    Figure yellow_circle = Figure(BOUND, 0.3, vec3(1, 1, 0), vec4(0, 0, -0.1, 1), vec4(.7, 0, .7, 0), vec4(0, 1, 0, 0));
    regFig(yellow_circle);
}

void loop (void) {
    renderLoop();   // this must be the last, I think
}

int main(void)
{
    init();
    while (!exitCondition()) {
        loop();
    }

    glfwTerminate();
    return 0;
}
