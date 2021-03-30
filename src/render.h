#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include "settings.h"

using glm::vec3;

void renderLoad ();
void renderLoop ();

void sendResolution ();
void changeSize (GLFWwindow* _, int w, int h);

bool exitCondition ();

float getMov(vec3 &ax);
float getRot(vec3 &ax);
