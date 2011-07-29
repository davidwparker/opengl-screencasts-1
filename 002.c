#include "screencasts.h"

/*  Globals */
double dim=2; /* dimension of orthogonal box */
char *windowName = "Bitmap chars";

/*
 *  Display the scene
 */
void display()
{
  /*  Clear the image */
  glClear(GL_COLOR_BUFFER_BIT);
  /*  Reset previous transforms */
  glLoadIdentity();

  /*  Draw something here */
  glBegin(GL_POLYGON);
  glColor3f(1.0,0.0,0.0);
  glVertex2f( 0.0, 0.5);
  glColor3f(0.0,1.0,0.0);
  glVertex2f( 0.5,-0.5);
  glColor3f(0.0,0.0,1.0);
  glVertex2f(-0.5,-0.5);
  glEnd();

  /*  Bitmap chars */
  glColor3f(1,1,1);
  printAt(5,5,"hello bitmap characters");
  glWindowPos2i(100,20);
  print("and again");
  
  /*  Flush and swap */
  glFlush();
  glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
  double w2h = (height>0) ? (double)width/height : 1;
  glViewport(0,0, width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(500,500);
  glutCreateWindow(windowName);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
