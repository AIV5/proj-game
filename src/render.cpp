#include "render.h"
#include <cmath>

float hw = .5f * PGS_START_WINDOW_WIDTH;
float hh = .5f * PGS_START_WINDOW_HEIGHT;

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

    GLuint point_loc = glGetUniformLocation(prog, "point");
    glUniform4f(point_loc, 0, 0, 0, 1);

    GLuint l1_loc = glGetUniformLocation(prog, "l1");
    glUniform4f(l1_loc, 0, sin(0.05), 0, cos(0.05));

    GLuint l2_loc = glGetUniformLocation(prog, "l2");
    glUniform4f(l2_loc, 0, 0, 1, 0);
}

void renderLoop () {
    glBindVertexArray(VAO);
    glDrawArrays(GL_QUADS, 0, 4);
}

void sendResolution () {
    GLuint hr_loc = glGetUniformLocation(prog, "hr");
    glUniform2f(hr_loc, hw, hh);
}

void changeSize (GLFWwindow* _, int w, int h) {
	hw = .5f * w;
	hh = .5f * h;
	glViewport(0, 0, w, h);
	sendResolution();
}
