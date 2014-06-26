#include <stdio.h> // For debugging 
#include <math.h> // Calculations to use later, not in this assignment
//Open GL includes
#include <GL/glut.h>
#include <GL/gl.h>

int main(int argc, char** argv) {
  glClear (GL_COLOR_BUFFER_BIT);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
}