#include <glm/glm.hpp>
#include "render.h"
#include "figure.h"
#include "shaderManager.h"

using glm::vec3;
using glm::vec4;

glm::vec2 hr = {.5f * PGS_START_WINDOW_WIDTH, .5f * PGS_START_WINDOW_HEIGHT};

GLFWwindow* window;
GLuint VAO;
GLuint prog;

void test () {
    glm::mat4 m;
    glm::vec4 v;
    std::cout << "test: " << sizeof(m) << " " << sizeof(v) << "\n";
}

void renderLoad () {
    test();
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

    GLuint pp_loc = glGetUniformLocation(prog, "playerP");
    glUniform4f(pp_loc, 1, 0, 0, 0);

    GLuint pr_loc = glGetUniformLocation(prog, "playerR");
    glUniform4f(pr_loc, 0, 1, 0, 0);

    GLuint pu_loc = glGetUniformLocation(prog, "playerU");
    glUniform4f(pu_loc, 0, 0, 1, 0);

    GLuint pf_loc = glGetUniformLocation(prog, "playerF");
    glUniform4f(pf_loc, 0, 0, 0, 1);

    Figure dot = Figure(vec3(1, 0, 1), vec4(0, 0, 0.1, 1));
    regFig(dot);
    Figure red_line = Figure(vec3(1, 0, 0), vec4(0, 0, 0.3, 1), vec4(0, 1, 0.1, 0));
    regFig(red_line);
    Figure green_line = Figure(vec3(0, 1, 0), vec4(0.1, 0, 0.3, .5), vec4(0, .1, 0.4, 1));
    regFig(green_line);
    Figure yellow_circle = Figure(BOUND, 0.3, vec3(1, 1, 0), vec4(0, 0, -0.1, 1), vec4(.7, 0, .7, 0), vec4(0, 1, 0, 0));
    regFig(yellow_circle);
}

void renderLoop () {
    glDrawArrays(GL_QUADS, 0, 4);
}

void sendResolution () {
    GLuint hr_loc = glGetUniformLocation(prog, "hr");
    glUniform2f(hr_loc, hr.x, hr.y);
}

void changeSize (GLFWwindow* _, int w, int h) {
    hr = .5f * glm::vec2(w, h);
	glViewport(0, 0, w, h);
	sendResolution();
}
