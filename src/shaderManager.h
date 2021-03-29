#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <glad/glad.h>
#include "settings.h"
#include "figure.h"

void loadShader (char *fileName, GLint shader);
GLuint loadProgram (void);

GLuint getArrayLoc (char* name, int index);

int regFig (Figure &figure);
void modFig (Figure &figure, int index);

void printMatrix (glm::mat4 m);
