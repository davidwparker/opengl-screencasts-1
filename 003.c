#include "screencasts.h"

/*  Poor man's approximation of PI */
#define PI 3.1415926535898
/*  Determine number of elements in an array  */
#define Length(x) (sizeof (x) / sizeof *(x))

/*  Globals */
double dim=2; /* dimension of orthogonal box */
char *windowName = "OpenGL screenscasts 3: Drawing points and lines";
int windowWidth=500;
int windowHeight=500;

/*
 *  Display the scene
 */
void display()
{
  int i;
  float angle;
  GLfloat vert1[2] = {0.0,0.5};
  GLfloat vert2[2] = {0.5,-0.5};
  GLfloat vert3[2] = {-0.5,-0.5};
  GLfloat vert4[4][2] = { {0.5,0.5},{0.5,-0.5},{-0.5,-0.5},{-0.5,0.5} };
  GLfloat color4[4][3] = { {0.0,1.0,0.0},{0.0,0.0,1.0},
			  {1.0,1.0,0.0},{1.0,0.0,1.0} };
  GLfloat color1[3] = {1.0,1.0,1.0};
  GLfloat color23[2][3] = { {0.0,1.0,0.0},{0.0,0.0,1.0} };
  
  /*  Clear the image */
  glClear(GL_COLOR_BUFFER_BIT);
  /*  Reset previous transforms */
  glLoadIdentity();

  /*  Draw something here */
  // GL_POINTS
  /*
  glPointSize(4.0);
  glBegin(GL_POINTS);
  glColor3fv( color1 );
  glVertex2fv( vert1 );
  glColor3fv( color23[0] );
  glVertex2fv( vert2 );
  glColor3fv( color23[1] );
  glVertex2fv( vert3 );
  glEnd();
  */

  // GL_LINES
  // 3 vertexes => 1 lines
  /*
  glBegin(GL_LINES);
  glColor3f(1.0,1.0,1.0);
  glVertex2f( 0.0, 0.5);
  glColor3f(0.0,1.0,0.0);
  glVertex2f( 0.5,-0.5);
  glColor3f(0.0,0.0,1.0);
  glVertex2f(-0.5,-0.5);
  glEnd();
  */

  // 4 vertexes => 2 lines
  /*
  glBegin(GL_LINES);
  glColor3f(1.0,1.0,1.0);
  glVertex2f( 0.5, 0.5);
  glColor3f(0.0,1.0,0.0);
  glVertex2f( 0.5,-0.5);
  glColor3f(0.0,0.0,1.0);
  glVertex2f(-0.5,-0.5);
  glColor3f(0.0,1.0,1.0);
  glVertex2f(-0.5,0.5);
  glEnd();
  */

  // GL_LINE_STRIP
  /*
  glBegin(GL_LINE_STRIP);
  glColor3f(1.0,1.0,1.0);
  glVertex2f( 0.5, 0.5);
  glColor3f(0.0,1.0,0.0);
  glVertex2f( 0.5,-0.5);
  glColor3f(0.0,0.0,1.0);
  glVertex2f(-0.5,-0.5);
  glColor3f(0.0,1.0,1.0);
  glVertex2f(-0.5,0.5);
  glEnd();
  */

  // GL_LINE_LOOP
  /*
  glBegin(GL_LINE_LOOP);
  glColor3f(1.0,1.0,1.0);
  glVertex2f( 0.5, 0.5);
  glColor3f(0.0,1.0,0.0);
  glVertex2f( 0.5,-0.5);
  glColor3f(0.0,0.0,1.0);
  glVertex2f(-0.5,-0.5);
  glColor3f(0.0,1.0,1.0);
  glVertex2f(-0.5,0.5);
  glEnd();
  */

  // Other constructs between glBegin and glEnd
  /*
  glBegin(GL_LINE_LOOP);
  for (i = 0; i < Length(color4); i++) {
    glColor3fv(color4[i]);
    glVertex3fv(vert4[i]);
  }
  glEnd();
  */

  /*
  glBegin(GL_LINE_LOOP);
  for (i = 0; i < 180; i++) {
    angle = 2*PI*i/180;
    glVertex2f(cos(angle), sin(angle));
  }
  glEnd();
  */
  // additional functions

  glLineWidth(3.0);
  glEnable(GL_LINE_STIPPLE);
  //glLineStipple(1, 0x00FF);
  //glLineStipple(2, 0x00FF);
  glLineStipple(3, 0x00FF);
  glBegin(GL_LINE_LOOP);
  glColor3f(1.0,1.0,1.0);
  glVertex2f( 0.5, 0.5);
  glColor3f(0.0,1.0,0.0);
  glVertex2f( 0.5,-0.5);
  glColor3f(0.0,0.0,1.0);
  glVertex2f(-0.5,-0.5);
  glColor3f(0.0,1.0,1.0);
  glVertex2f(-0.5,0.5);
  glEnd();


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
 *  windowKey
 *  ------
 *  GLUT calls this routine when a non-special key is pressed
 */
void windowKey(unsigned char key,int x,int y)
{
  /*  Exit on ESC */
  if (key == 27) exit(0);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(windowWidth,windowHeight);
  glutCreateWindow(windowName);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(windowKey);

  glutMainLoop();
  return 0;
}
