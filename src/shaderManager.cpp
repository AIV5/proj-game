#include <cstdio>
#include <cstring>
#include <iostream>
#include <glad/glad.h>
#include "settings.h"
#include "shaderManager.h"

extern GLuint prog;
int objCount = 0;

void loadShader (char *fileName, GLuint shader) {
    char* code = (char *)malloc(PGS_SHADER_FILE_SIZE);
    memset(code, 0, PGS_SHADER_FILE_SIZE);
    FILE *fin = fopen(fileName, "rb");
    if (fin) {
        fread(code, 1, PGS_SHADER_FILE_SIZE, fin);
        fclose(fin);
    } else {
        std::cout << "Error when loading shader. File " << fileName << " not found\n";
        free(code);
        exit(-1);
    }
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    free(code);

    GLint ok;
    GLchar log[2000];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        glGetShaderInfoLog(shader, 2000, NULL, log);
        std::cout << "Error when compiling shader " << fileName << "\nlog:\n" << log << "\n";
        exit(-1);
    }
}

GLuint loadProgram () {
    GLuint prog = glCreateProgram();
    //GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    //loadShader(PGS_VERTEX_SHADER_NAME, vertShader);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    loadShader(PGS_FRAGMENT_SHADER_NAME, fragShader);
    //glAttachShader(prog, vertShader);
    glAttachShader(prog, fragShader);
    //glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    glLinkProgram(prog);

    GLint ok;
    GLchar log[2000];
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        glGetProgramInfoLog(prog, 2000, NULL, log);
        std::cout << "Error when linking program\nlog:\n" << log << "\n";
        exit(-1);
    }
    return prog;
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

int regFig (Figure &figure) {
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
    glm::mat4 PM = basis * glm::transpose(basis);
    glUniformMatrix4fv(objPMLoc, 1, GL_FALSE, &PM[0][0]);
    glUniform4f(objColorLoc, figure.objColor[0], figure.objColor[1], figure.objColor[2], 1);
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

void modFig (Figure &figure, int index) {
    GLuint objNumberLoc = getArrayLoc("objNumber", index);
    GLuint objTypeLoc = getArrayLoc("objType", index);
    GLuint objPMLoc = getArrayLoc("objPM", index);
    GLuint objColorLoc = getArrayLoc("objColor", index);
    GLuint objCenterLoc = getArrayLoc("objCenter", index);
    GLuint objRadLoc = getArrayLoc("objRad", index);
    glUniform1i(objNumberLoc, objCount);
    glUniform1i(objTypeLoc, figure.objType);
    glm::mat4 basis = glm::mat4(figure.objCoord[0], figure.objCoord[1], figure.objCoord[2], figure.objCoord[3]);
    glm::mat4 PM = basis * glm::transpose(basis);
    glUniformMatrix4fv(objPMLoc, 1, GL_FALSE, &PM[0][0]);
    glUniform4f(objColorLoc, figure.objColor[0], figure.objColor[1], figure.objColor[2], 1);
    glUniform4fv(objCenterLoc, 1, &figure.objCoord[0][0]);
    glUniform1f(objRadLoc, figure.objRad);
}

void setPlayer (glm::mat4 coord) {
    GLuint PLoc = glGetUniformLocation(prog, "playerP");
    GLuint RLoc = glGetUniformLocation(prog, "playerR");
    GLuint ULoc = glGetUniformLocation(prog, "playerU");
    GLuint FLoc = glGetUniformLocation(prog, "playerF");
    glUniform4fv(PLoc, 1, &coord[0][0]);
    glUniform4fv(RLoc, 1, &coord[1][0]);
    glUniform4fv(ULoc, 1, &coord[2][0]);
    glUniform4fv(FLoc, 1, &coord[3][0]);
}
