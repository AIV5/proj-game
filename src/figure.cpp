#include <iostream>
#include "figure.h"

void _errorMinVectorLength () {
    std::cout << "Error when constructing a figure. Degenerate vector sistem was given.\n";
    exit(-1);
}

Figure::Figure(void) {
    std::cout << "Error when constructing a figure. Empty constructor called.";
}

Figure::Figure(glm::vec3 color, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f) {
    init(color, p, r, u, f);
    objType = FULL;
}


Figure::Figure(_objType_t type, float rad, glm::vec3 color, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f) {
    init(color, p, r, u, f);
    objType = type;
    objRad = rad;
}


glm::vec4 orthonormal (glm::vec4 f, glm::vec4 u, glm::vec4 r, glm::vec4 p) {
    if (f == nullVec)
        return nullVec;
    if (glm::length(f) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    f = glm::normalize(f);
    f = f - p * glm::dot(p, f) - r * glm::dot(r, f)  - u * glm::dot(u, f);
    if (glm::length(f) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    f = glm::normalize(f);
    return f;
}

void Figure::init (glm::vec3 color, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f) {
    objIndex = -1;
    objColor = color;
    p = orthonormal(p);
    if (p == nullVec)
        _errorMinVectorLength();
    r = orthonormal(r, p);
    if (r == nullVec) {
        if (u != nullVec || f != nullVec)
            _errorMinVectorLength();
    } else {
        u = orthonormal(u, r, p);
        if (u == nullVec) {
            if (f != nullVec)
            _errorMinVectorLength();
        } else {
            f = orthonormal(f, u, r, p);
        }
    }
    objCoord[0] = p;
    objCoord[1] = r;
    objCoord[2] = u;
    objCoord[3] = f;
}
