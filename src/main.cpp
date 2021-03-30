#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "render.h"
#include "shaderManager.h"
#include <unistd.h>
#include <iostream>

extern GLFWwindow* window;
using glm::vec3;
using glm::vec4;
using glm::mat4;

mat4 player = mat4(1);

mat4 movMat () {
    vec3 ax;
    float a = getMov(ax);
    float c = cos(a);
    float v = 1 - c;
    float s = sin(a);
    mat4 m;
    m[0] = vec4(c, ax * s);
    m[1] = vec4(-ax.x * s, 1 - ax.x*ax.x*v, -ax.x*ax.y*v, -ax.x*ax.z*v);
    m[2] = vec4(-ax.y * s, -ax.x*ax.y*v, 1 - ax.y*ax.y*v, -ax.y*ax.z*v);
    m[3] = vec4(-ax.z * s, -ax.x*ax.z*v, -ax.y*ax.z*v, 1 - ax.z*ax.z*v);
    return player * m * transpose(player);
}

mat4 rotMat () {
    vec3 ax;
    float a = getRot(ax);
    float c = cos(a);
    float v = 1 - c;
    float s = sin(a);
    float x = ax.x, y = ax.y, z = ax.z;
    mat4 m;
    m[0] = vec4(1, 0, 0, 0);
    m[1] = vec4(0, c + v*x*x, v*y*x + s*z, c*z*x - s*y);
    m[2] = vec4(0, v*x*y - s*z, c + v*y*y, v*z*y + s*x);
    m[3] = vec4(0, v*x*z + s*y, v*y*z - s*x, c + v*z*z);
    std::cout << "ax:\n";
    printVector(vec4(0, ax));
    std::cout << "R:\n";
    printMatrix(m);
    return player * m * transpose(player);
}

void init (void) {
    renderLoad();   // this must be the first, I think
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
    player = rotMat() * player;
    setPlayer(player);
    renderLoop();   // this must be the last, I think
    sleep(1);
    std::cout << '\n';
    printVector(player[0]);
    std::cout << '\n';
    printMatrix(player * transpose(player));
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
