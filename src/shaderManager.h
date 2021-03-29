#pragma once

#include "figure.h"

void loadShader (char *fileName, GLint shader);
GLuint loadProgram (void);

GLuint getArrayLoc (char* name, int index);

int regFig (Figure &figure);
void modFig (Figure &figure, int index);

void setPlayer (glm::mat4 coord);

void printMatrix (glm::mat4 m);
