/* A simple program to show how to set up an X window for OpenGL rendering.
 * X86 compilation: gcc -o -L/usr/X11/lib   main main.c -lGL -lX11
 * X64 compilation: gcc -o -L/usr/X11/lib64 main main.c -lGL -lX11
 */
#include <stdio.h>
#include <stdlib.h>

#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <X11/X.h>    /* X11 constant (e.g. TrueColor) */
#include <X11/keysym.h>

#include "raytracer.h"

RayTracer tracer;

void fatalError(char *message)
{
  fprintf(stderr, "main: %s\n", message);
  exit(1);
}

void display (void)
{
  //glClearColor (0.2,0.0,0.2,1.0);
  glClear (GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glBegin(GL_POINTS);
  tracer.Trace( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
  glEnd();
  glFlush();
}

void reshape (int w, int h)
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho( 0, 300 , 0 , 300, -1, 1 );
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

}
void keyboard (unsigned char key, int x, int y)
{
  if (key==27)
  { //27 is the ascii code for the ESC key
    exit (0); //end the program
  }
}

int main(int argc, char **argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize (300, 300);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("RayTrac0r");
  glDisable(GL_LIGHTING);

  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutKeyboardFunc (keyboard);//the call for the keyboard function.

  glutMainLoop ();

  return 0;
}
