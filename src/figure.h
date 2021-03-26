#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

enum _objType_t {FULL, LIMITED, BOUND};

class Figure {
public:
    int objIndex;
    int objType;
    glm::vec4 objCoord[4];
    glm::vec4 objColor;
    float objRad;
    Figure(void);
    Figure(glm::vec4 p, glm::vec4 color);
    Figure(glm::vec4 p, glm::vec4 r, glm::vec4 color);
    Figure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color);
    Figure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color);
    Figure(_objType_t type, glm::vec4 p, glm::vec4 color, float rad);
    Figure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 color, float rad);
    Figure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color, float rad);
    Figure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color, float rad);
};

GLuint getArrayLoc (char* name, int index);

int registerFigure(Figure &figure);
void modifyFigure(Figure &figure, int index);

int createFigure(glm::vec4 p, glm::vec4 color);
int createFigure(glm::vec4 p, glm::vec4 r, glm::vec4 color);
int createFigure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color);
int createFigure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color);
int createFigure(_objType_t type, glm::vec4 p, glm::vec4 color, float rad);
int createFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 color, float rad);
int createFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color, float rad);
int createFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color, float rad);

void configFigure(glm::vec4 p, glm::vec4 color, int index);
void configFigure(glm::vec4 p, glm::vec4 r, glm::vec4 color, int index);
void configFigure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color, int index);
void configFigure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color, int index);
void configFigure(_objType_t type, glm::vec4 p, glm::vec4 color, float rad, int index);
void configFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 color, float rad, int index);
void configFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color, float rad, int index);
void configFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color, float rad, int index);
