#pragma once
#define GLEW_STATIC
#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void makeGLint(GLuint *a, GLuint *b, GLuint g);
void makeGLfloat(GLfloat *a, GLfloat *b, GLuint g);
void makeTrueIndAndColor(int Node, int *leng, GLuint indices, GLfloat colors);
