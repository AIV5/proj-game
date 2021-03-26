#include "render.h"
#include <glm/glm.hpp>
#include "figure.h"

glm::vec2 hr = {.5f * PGS_START_WINDOW_WIDTH, .5f * PGS_START_WINDOW_HEIGHT};

GLFWwindow* window;
GLuint VAO;
GLuint prog;

void renderLoad () {
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

    createFigure(glm::vec4(0, 0, 0, 1), glm::vec4(0, 1, .1, 0), glm::vec4(0, 1, 0, 1));
    createFigure(glm::vec4(0, 0, 1, 0), glm::vec4(0, .5, .1, 1), glm::vec4(1, 0, 0, 1));
    createFigure(BOUND, glm::vec4(0, 0, 0, 1), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(1, 1, 0, 1), .2);
    createFigure(glm::vec4(0, 0, .1, 1), glm::vec4(0, 0, 1, 1));
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
