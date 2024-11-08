#pragma once
#include <GL/gl.h>

// This is the only function we need from GLU.
// Copied the implementation from:
// https://gitlab.freedesktop.org/mesa/glu/-/blob/a2b96c7bba8db8fec3e02fb4227a7f7b02cabad1/src/libutil/project.c
void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
