#include "screencasts.h"

/*  Globals */
double dim=3.0; /* dimension of orthogonal box */
char *windowName = "OpenGL screenscasts 6: Drawing in 3d part 1: GLUT objects";
int windowWidth=500;
int windowHeight=450;

/*  Various global state */
/*  Toggles */
int toggleAxes = 0;   /* toggle axes on and off */
int toggleValues = 1; /* toggle values on and off */

/*  Display view */
int th = 0;  /* azimuth of view angle */
int ph = 0;  /* elevation of view angle */

/*  Objects */
int objId = 0;      /* object to draw */
int objSlices = 16; /* slices lines of longitude */
int objStacks = 16; /* stacks lines of latitude */

/*
 * drawAxes()
 * ------
 * Draw the axes
 */
void drawAxes() 
{
  if (toggleAxes) {
    /*  Length of axes */
    double len = 2.0;
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(len,0,0);
    glVertex3d(0,0,0);
    glVertex3d(0,len,0);
    glVertex3d(0,0,0);
    glVertex3d(0,0,len);
    glEnd();
    /*  Label axes */
    glRasterPos3d(len,0,0);
    print("X");
    glRasterPos3d(0,len,0);
    print("Y");
    glRasterPos3d(0,0,len);
    print("Z");
  }
}

/*
 *  drawValues()
 *  ------
 *  Draw the values in the lower left corner
 */
void drawValues()
{
  if (toggleValues) {
    glColor3f(1.0,1.0,1.0);
    printAt(5,5,"View Angle (th, ph) =(%d, %d)", th,ph);
  }
}

/*
 *  drawShape()
 *  ------
 *  Draw the GLUT shape
 */
void drawShape()
{
  glColor3f(1.0,1.0,0.0);

  // objId == 0 => draw nothing
  if (objId == 1)
    glutWireSphere(1,objSlices,objStacks);
  else if (objId == 2)
    glutSolidSphere(1,objSlices,objStacks);
  else if (objId == 3)
    glutWireCube(1);
  else if (objId == 4)
    glutSolidCube(1);
  else if (objId == 5)
    glutWireCone(1,2,objSlices,objStacks);
  else if (objId == 6)
    glutSolidCone(1,2,objSlices,objStacks);
  else if (objId == 7)
    glutWireTorus(1,2,objSlices,objStacks);
  else if (objId == 8)
    glutSolidTorus(1,2,objSlices,objStacks);
  else if (objId == 9)
    glutWireIcosahedron();
  else if (objId == 10)
    glutSolidIcosahedron();
  else if (objId == 11)
    glutWireOctahedron();
  else if (objId == 12)
    glutSolidOctahedron();
  else if (objId == 13)
    glutWireTetrahedron();
  else if (objId == 14)
    glutSolidTetrahedron();
  else if (objId == 15)
    glutWireDodecahedron();
  else if (objId == 16)
    glutSolidDodecahedron();

  // NOTE: only the teapot generates with normals and texture coordinates
  else if (objId == 17)
    glutWireTeapot();
  else if (objId == 18)
    glutSolidTeapot();
}

/*
 *  display()
 *  ------
 *  Display the scene
 */
void display()
{
  /*  Clear the image */
  glClear(GL_COLOR_BUFFER_BIT);
  /*  Reset previous transforms */
  glLoadIdentity();

  /*  Set View Angle */
  glRotated(ph,1,0,0);
  glRotated(th,0,1,0);

  /*  Draw  */
  drawAxes();
  drawValues();
  drawShape();

  /*  Flush and swap */
  glFlush();
  glutSwapBuffers();
}

/*
 *  reshape()
 *  ------
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
  double w2h = (height>0) ? (double)width/height : 1;
  glViewport(0,0, width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /* orthogonal projection */
  glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*
 *  windowKey()
 *  ------
 *  GLUT calls this routine when a non-special key is pressed
 */
void windowKey(unsigned char key,int x,int y)
{
  /*  Exit on ESC */
  if (key == 27) exit(0);
  else if (key == 'a' || key == 'A') toggleAxes = 1-toggleAxes;
  else if (key == 'v' || key == 'V') toggleValues = 1-toggleValues;

  /*  Spacebar - Toggle through shapes */
  else if (key == 32) {
    if (objId == 18) objId = 0;
    else objId++;
  }

  glutPostRedisplay();
}

/*
 *  windowSpecial()
 *  ------
 *  GLUT calls this routine when an arrow key is pressed
 */
void windowSpecial(int key,int x,int y)
{
  /*  Right arrow key - increase azimuth by 5 degrees */
  if (key == GLUT_KEY_RIGHT) th += 5;
  /*  Left arrow key - decrease azimuth by 5 degrees */
  else if (key == GLUT_KEY_LEFT) th -= 5;
  /*  Up arrow key - increase elevation by 5 degrees */
  else if (key == GLUT_KEY_UP) ph += 5;
  /*  Down arrow key - decrease elevation by 5 degrees */
  else if (key == GLUT_KEY_DOWN) ph -= 5;

  /*  Keep angles to +/-360 degrees */
  th %= 360;
  ph %= 360;

  glutPostRedisplay();
}

/*
 *  windowMenu
 *  ------
 *  Window menu is the same as the keyboard clicks
 */
void windowMenu(int value)
{
  windowKey((unsigned char)value, 0, 0);
}

/*
 *  main()
 *  ----
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

  glutCreateMenu(windowMenu);
  glutAddMenuEntry("Toggle Axes [a]",'a');
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}
