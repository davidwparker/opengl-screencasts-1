#include "screencasts.h"

/*  Globals */
double dim=2; /* dimension of orthogonal box */
char *windowName = "OpenGL screenscasts 5: Using GLUT for OpenGL interaction";
int windowWidth=500;
int windowHeight=450;

/* global state */
char *mouseBtnPressed = "";
char *mouseState = "";
int keyPressed = 0;
char *specialPressed = "";
char *modifiers = "";
int mouseX,mouseY = 0;

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
  printAt(5,105, "mouse button = %s", mouseBtnPressed);
  printAt(5,85, "mouse state = %s", mouseState);
  printAt(5,65, "key = %d", keyPressed);
  printAt(5,45, "special = %s", specialPressed);
  printAt(5,25, "modifiers = %s", modifiers);
  printAt(5,05, "mouse x=%d, mouse y=%d", mouseX,mouseY);

  /*  Flush and swap */
  glFlush();
  glutSwapBuffers();
}

/*
 *  windowKey
 *  ------
 *  GLUT calls this when a non-special key is pressed
 */
void windowKey(unsigned char key,int x,int y)
{
  int currModifiers = glutGetModifiers();
  /*  Exit on ESC */
  if (key == 27) exit(0);
  else if (key == 'a' || key == 'A')
    keyPressed = -10;
  else {
    keyPressed = key;
  }

  if (currModifiers == GLUT_ACTIVE_SHIFT)
    modifiers = "SHIFT";
  else if (currModifiers == GLUT_ACTIVE_CTRL)
    modifiers = "CTRL";

  glutPostRedisplay();
}

/*
 *  windowSpecial
 *  ------
 *  GLUT calls this when a special key is pressed
 */
void windowSpecial(int key,int x,int y)
{
  int currModifiers = glutGetModifiers();
  if (key == GLUT_KEY_RIGHT)
    specialPressed = "Right Key";
  else if (key == GLUT_KEY_F1)
    specialPressed = "F1";
  
  if (currModifiers == GLUT_ACTIVE_SHIFT)
    modifiers = "SHIFT";
  else if (currModifiers == GLUT_ACTIVE_CTRL)
    modifiers = "CTRL";

  glutPostRedisplay();
}

/*
 *  windowMouse
 *  ------
 *  GLUT calls this when the mouse is clicked down or up
 */ 
void windowMouse(int btn, int state, int x, int y)
{
  if (btn == GLUT_LEFT_BUTTON)
    mouseBtnPressed = "Left";
  else if(btn == GLUT_RIGHT_BUTTON)
    mouseBtnPressed = "Right";

  if (state == GLUT_DOWN)
    mouseState = "down";
  else if(state == GLUT_UP)
    mouseState = "up";

  glutPostRedisplay();
}

/*
 *  windowPmotion
 *  ------
 *  GLUT calls this whenever the mouse is moved
 */ 
void windowPmotion(int x, int y)
{
  mouseX = x;
  mouseY = y;
  glutPostRedisplay();
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
  glutInitWindowSize(windowWidth,windowHeight);
  glutCreateWindow(windowName);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glutKeyboardFunc(windowKey);
  glutSpecialFunc(windowSpecial);
  glutMouseFunc(windowMouse);
  glutPassiveMotionFunc(windowPmotion);

  glutMainLoop();
  return 0;
}

