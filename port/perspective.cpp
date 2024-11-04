#include <GL/gl.h>
#include <cmath>

static void __gluMakeIdentityd(GLdouble m[16]) {
  m[0 + 4 * 0] = 1;
  m[0 + 4 * 1] = 0;
  m[0 + 4 * 2] = 0;
  m[0 + 4 * 3] = 0;
  m[1 + 4 * 0] = 0;
  m[1 + 4 * 1] = 1;
  m[1 + 4 * 2] = 0;
  m[1 + 4 * 3] = 0;
  m[2 + 4 * 0] = 0;
  m[2 + 4 * 1] = 0;
  m[2 + 4 * 2] = 1;
  m[2 + 4 * 3] = 0;
  m[3 + 4 * 0] = 0;
  m[3 + 4 * 1] = 0;
  m[3 + 4 * 2] = 0;
  m[3 + 4 * 3] = 1;
}

#define __glPi 3.14159265358979323846

void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
  GLdouble m[4][4];
  double sine, cotangent, deltaZ;
  double radians = fovy / 2 * __glPi / 180;

  deltaZ = zFar - zNear;
  sine = sin(radians);
  if ((deltaZ == 0) || (sine == 0) || (aspect == 0)) {
    return;
  }
  cotangent = cosf(radians) / sine;

  __gluMakeIdentityd(&m[0][0]);
  m[0][0] = cotangent / aspect;
  m[1][1] = cotangent;
  m[2][2] = -(zFar + zNear) / deltaZ;
  m[2][3] = -1;
  m[3][2] = -2 * zNear * zFar / deltaZ;
  m[3][3] = 0;
  glMultMatrixd(&m[0][0]);
}
