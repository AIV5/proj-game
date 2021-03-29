#pragma once

#include <glm/glm.hpp>

#define PGS_MIN_VECTOR_LENGTH 0.001f

enum _objType_t {FULL, LIMITED, BOUND};
const glm::vec4 nullVec = glm::vec4(0, 0, 0, 0);

class Figure {
private:
    void init (glm::vec3 color, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f);
public:
    int objIndex;
    int objType;
    glm::vec3 objColor;
    float objRad;
    glm::vec4 objCoord[4];
    Figure(void);
    Figure(glm::vec3 color, glm::vec4 p, glm::vec4 r=nullVec, glm::vec4 u=nullVec, glm::vec4 f=nullVec);
    Figure(_objType_t type, float rad, glm::vec3 color, glm::vec4 p, glm::vec4 r=nullVec, glm::vec4 u=nullVec, glm::vec4 f=nullVec);
};

glm::vec4 orthonormal (glm::vec4 f, glm::vec4 u=nullVec, glm::vec4 r=nullVec, glm::vec4 p=nullVec);
