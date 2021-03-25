#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <glad/glad.h>
#include "settings.h"

void loadShader (char *fileName, GLint shader);
GLuint loadProgram (void);
