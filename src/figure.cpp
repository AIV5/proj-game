#include "figure.h"
#include <cstdio>
#include <cstring>

extern GLuint prog;
int objCount = 0;

void _errorMinVectorLength () {
    std::cout << "Error when constructing a figure. Degenerate vector sistem was given.\n";
    exit(1);
}

Figure::Figure(void) {
    std::cout << "Error when constructing a figure. Empty constructor called.";
}

Figure::Figure (glm::vec4 p, glm::vec4 color) {
    objType = FULL;
    if (glm::length(p) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    p = glm::normalize(p);
    objCoord[0] = p;
    objCoord[1] = glm::vec4(0);
    objCoord[2] = glm::vec4(0);
    objCoord[3] = glm::vec4(0);
    objColor = glm::vec4(color);
}

Figure::Figure(glm::vec4 p, glm::vec4 r, glm::vec4 color) {
    objType = FULL;
    if (glm::length(p) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    p = glm::normalize(p);
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    r = glm::normalize(r);
    r = r - p * glm::dot(p, r);
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    r = glm::normalize(r);
    objCoord[0] = p;
    objCoord[1] = r;
    objCoord[2] = glm::vec4(0);
    objCoord[3] = glm::vec4(0);
    objColor = glm::vec4(color);
}

Figure::Figure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color) {
    objType = FULL;
    if (glm::length(p) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    if (glm::length(u) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    p = glm::normalize(p);
    r = glm::normalize(r);
    u = glm::normalize(u);
    r = r - p * glm::dot(p, r);
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    r = glm::normalize(r);
    u = u - p * glm::dot(p, u) - r * glm::dot(r, u);
    if (glm::length(u) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    u = glm::normalize(u);
    objCoord[0] = p;
    objCoord[1] = r;
    objCoord[2] = u;
    objCoord[3] = glm::vec4(0);
    objColor = glm::vec4(color);
}

Figure::Figure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color) {
    objType = FULL;
    if (glm::length(p) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    if (glm::length(u) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    if (glm::length(f) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    p = glm::normalize(p);
    r = glm::normalize(r);
    u = glm::normalize(u);
    f = glm::normalize(f);
    r = r - p * glm::dot(p, r);
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    r = glm::normalize(r);
    u = u - p * glm::dot(p, u) - r * glm::dot(r, u);
    if (glm::length(u) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    u = glm::normalize(u);
    f = f - p * glm::dot(p, f) - r * glm::dot(r, f)  - u * glm::dot(u, f);
    if (glm::length(f) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    f = glm::normalize(f);
    objCoord[0] = p;
    objCoord[1] = r;
    objCoord[2] = u;
    objCoord[3] = f;
    objColor = glm::vec4(color);
}

Figure::Figure(_objType_t type, glm::vec4 p, glm::vec4 color, float rad) {
    objType = type;
    if (glm::length(p) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    p = glm::normalize(p);
    objCoord[0] = p;
    objCoord[1] = glm::vec4(0);
    objCoord[2] = glm::vec4(0);
    objCoord[3] = glm::vec4(0);
    objColor = glm::vec4(color);
    objRad = rad;
}

Figure::Figure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 color, float rad) {
    objType = type;
    if (glm::length(p) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    p = glm::normalize(p);
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    r = glm::normalize(r);
    r = r - p * glm::dot(p, r);
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    r = glm::normalize(r);
    objCoord[0] = p;
    objCoord[1] = r;
    objCoord[2] = glm::vec4(0);
    objCoord[3] = glm::vec4(0);
    objColor = glm::vec4(color);
    objRad = rad;
}

Figure::Figure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color, float rad) {
    objType = type;
    if (glm::length(p) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    if (glm::length(u) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    p = glm::normalize(p);
    r = glm::normalize(r);
    u = glm::normalize(u);
    r = r - p * glm::dot(p, r);
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    r = glm::normalize(r);
    u = u - p * glm::dot(p, u) - r * glm::dot(r, u);
    if (glm::length(u) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    u = glm::normalize(u);
    objCoord[0] = p;
    objCoord[1] = r;
    objCoord[2] = u;
    objCoord[3] = glm::vec4(0);
    objColor = glm::vec4(color);
    objRad = rad;
}

Figure::Figure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color, float rad) {
    objType = type;
    if (glm::length(p) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    if (glm::length(u) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    if (glm::length(f) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    p = glm::normalize(p);
    r = glm::normalize(r);
    u = glm::normalize(u);
    f = glm::normalize(f);
    r = r - p * glm::dot(p, r);
    if (glm::length(r) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    r = glm::normalize(r);
    u = u - p * glm::dot(p, u) - r * glm::dot(r, u);
    if (glm::length(u) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    u = glm::normalize(u);
    f = f - p * glm::dot(p, f) - r * glm::dot(r, f)  - u * glm::dot(u, f);
    if (glm::length(f) < PGS_MIN_VECTOR_LENGTH)
        _errorMinVectorLength();
    f = glm::normalize(f);
    objCoord[0] = p;
    objCoord[1] = r;
    objCoord[2] = u;
    objCoord[3] = f;
    objColor = glm::vec4(color);
    objRad = rad;
}

GLuint getArrayLoc (char* name, int index) {
    char text [32];
    sprintf(text, "%s[%d]", name, index);
    return glGetUniformLocation(prog, text);
}

void printMatrix (glm::mat4 m) {
    std::cout << m[0][0] << ' ' << m[1][0] << ' ' << m[2][0] << ' ' << m[3][0] << '\n';
    std::cout << m[0][1] << ' ' << m[1][1] << ' ' << m[2][1] << ' ' << m[3][1] << '\n';
    std::cout << m[0][2] << ' ' << m[1][2] << ' ' << m[2][2] << ' ' << m[3][2] << '\n';
    std::cout << m[0][3] << ' ' << m[1][3] << ' ' << m[2][3] << ' ' << m[3][3] << '\n';
}

int registerFigure(Figure &figure) {
    figure.objIndex = objCount;
    GLuint objNumberLoc = glGetUniformLocation(prog, "objNumber");
    GLuint objTypeLoc = getArrayLoc("objType", objCount);
    GLuint objPMLoc = getArrayLoc("objPM", objCount);
    GLuint objColorLoc = getArrayLoc("objColor", objCount);
    GLuint objCenterLoc = getArrayLoc("objCenter", objCount);
    GLuint objRadLoc = getArrayLoc("objRad", objCount);
    ++objCount;
    glUniform1i(objNumberLoc, objCount);
    glUniform1i(objTypeLoc, figure.objType);
    glm::mat4 basis = glm::mat4(figure.objCoord[0], figure.objCoord[1], figure.objCoord[2], figure.objCoord[3]);
    //memccpy(&basis[0][0], figure.objCoord, 1, sizeof(figure.objCoord));
    glm::mat4 PM = basis * glm::transpose(basis);
    glUniformMatrix4fv(objPMLoc, 1, GL_FALSE, &PM[0][0]);
    glUniform4fv(objColorLoc, 1, &figure.objColor[0]);
    glUniform4fv(objCenterLoc, 1, &figure.objCoord[0][0]);
    glUniform1f(objRadLoc, figure.objRad);

    std::cout << "figure: " << figure.objIndex << "\n";

    std::cout << "basis:\n";
    printMatrix(basis);

    std::cout << "transpose(basis)\n";
    printMatrix(glm::transpose(basis));

    std::cout << " PM:\n";
    printMatrix(PM);

    return figure.objIndex;
}

void modifyFigure(Figure &figure, int index) {
    GLuint objNumberLoc = getArrayLoc("objNumber", index);
    GLuint objTypeLoc = getArrayLoc("objType", index);
    GLuint objPMLoc = getArrayLoc("objPM", index);
    GLuint objColorLoc = getArrayLoc("objColor", index);
    GLuint objCenterLoc = getArrayLoc("objCenter", index);
    GLuint objRadLoc = getArrayLoc("objRad", index);
    glUniform1i(objTypeLoc, figure.objType);
    glm::mat4 basis = glm::mat4(figure.objCoord[0], figure.objCoord[1], figure.objCoord[2], figure.objCoord[3]);
    glm::mat4 PM = basis * glm::transpose(basis);
    glUniformMatrix4fv(objPMLoc, 1, GL_FALSE, &PM[0][0]);
    glUniform4fv(objColorLoc, 1, &figure.objColor[0]);
    glUniform4fv(objCenterLoc, 1, &figure.objCoord[0][0]);
    glUniform1f(objRadLoc, figure.objRad);
}

int createFigure(glm::vec4 p, glm::vec4 color) {
    Figure figure = Figure(p, color);
    return registerFigure(figure);
}

int createFigure(glm::vec4 p, glm::vec4 r, glm::vec4 color) {
    Figure figure = Figure(p, r, color);
    return registerFigure(figure);
}

int createFigure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color) {
    Figure figure = Figure(p, r, u, color);
    return registerFigure(figure);
}

int createFigure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color) {
    Figure figure = Figure(p, r, u, f, color);
    return registerFigure(figure);
}

int createFigure(_objType_t type, glm::vec4 p, glm::vec4 color, float rad) {
    Figure figure = Figure(type, p, color, rad);
    return registerFigure(figure);
}

int createFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 color, float rad) {
    Figure figure = Figure(type, p, r, color, rad);
    return registerFigure(figure);
}

int createFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color, float rad) {
    Figure figure = Figure(type, p, r, u, color, rad);
    return registerFigure(figure);
}

int createFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color, float rad) {
    Figure figure = Figure(type, p, r, u, f, color, rad);
    return registerFigure(figure);
}


void configFigure(glm::vec4 p, glm::vec4 color, int index) {
    Figure figure = Figure(p, color);
    modifyFigure(figure, index);
}

void configFigure(glm::vec4 p, glm::vec4 r, glm::vec4 color, int index) {
    Figure figure = Figure(p, r, color);
    modifyFigure(figure, index);
}

void configFigure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color, int index) {
    Figure figure = Figure(p, r, u, color);
    modifyFigure(figure, index);
}

void configFigure(glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color, int index) {
    Figure figure = Figure(p, r, u, f, color);
    modifyFigure(figure, index);
}

void configFigure(_objType_t type, glm::vec4 p, glm::vec4 color, float rad, int index) {
    Figure figure = Figure(type, p, color, rad);
    modifyFigure(figure, index);
}

void configFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 color, float rad, int index) {
    Figure figure = Figure(type, p, r, color, rad);
    modifyFigure(figure, index);
}

void configFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 color, float rad, int index) {
    Figure figure = Figure(type, p, r, u, color, rad);
    modifyFigure(figure, index);
}

void configFigure(_objType_t type, glm::vec4 p, glm::vec4 r, glm::vec4 u, glm::vec4 f, glm::vec4 color, float rad, int index) {
    Figure figure = Figure(type, p, r, u, f, color, rad);
    modifyFigure(figure, index);
}
