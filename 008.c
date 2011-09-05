#include "screencasts.h"

/*  Poor man's approximation of PI */
#define PI 3.1415926535898
/*  Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
/*  D degrees of rotation */
#define DEF_D 5

/*  Globals */
double dim=2.0; /* dimension of orthogonal box */
char *windowName="OpenGL screenscasts 8: Drawing in 3d part 3: Spheres, Cylinders, and Cones";
int windowWidth=500;
int windowHeight=450;

/*  Various global state */
int toggleAxes = 0;   /* toggle axes on and off */
int toggleValues = 1; /* toggle values on and off */
int toggleMode = 0;   /* projection mode */
int th = 0;   /* azimuth of view angle */
int ph = 0;   /* elevation of view angle */
int fov = 55; /* field of view for perspective */
int asp = 1;  /* aspect ratio */

int objId = 0;      /* object to draw */

/*
 * project()
 * ------
 * Sets the projection
 */
void project() 
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (toggleMode) {
    /* perspective */
    gluPerspective(fov,asp,dim/4,4*dim);
  }
  else {
    /* orthogonal projection*/
    glOrtho(-dim*asp,+dim*asp, -dim,+dim, -dim,+dim);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*
 * setEye()
 * ------
 * Set the eye position
 */
void setEye()
{
  if (toggleMode) {
    double Ex = -2*dim*Sin(th)*Cos(ph);
    double Ey = +2*dim        *Sin(ph);
    double Ez = +2*dim*Cos(th)*Cos(ph);
    /* camera/eye position, aim of camera lens, up-vector */
    gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
  }
  /*  Orthogonal - set world orientation */
  else {
    glRotatef(ph,1,0,0);
    glRotatef(th,0,1,0);
  }
}

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
    glColor3f(0.8,0.8,0.8);
    printAt(5,5,"View Angle (th, ph) =(%d, %d)", th,ph);
    printAt(5,25,"Projection mode =(%s)", toggleMode?"Perspective":"Orthogonal");
  }
}

/*
 *  vertex
 *  ------
 *  Draw vertex in polar coordinates 
 */
void vertex(double th2,double ph2)
{
   double x = Sin(th2)*Cos(ph2);
   double y = Cos(th2)*Cos(ph2);
   double z =          Sin(ph2);
   glVertex3d(x,y,z);
}

/*
 *  drawShape()
 *  ------
 *  Draw the GLUT shape
 */
void drawShape()
{
  int th2, ph2, i, j, k;
  // objId == 0 => draw nothing
  /* Sphere */
  if (objId == 1) {
    for (ph2=-90;ph2<90;ph2+=DEF_D) {
      glBegin(GL_QUAD_STRIP);
      for (th2=0;th2<=360;th2+=2*DEF_D) {
	glColor3f(0.0,1.0,0.0); //green
	vertex(th2,ph2);
	glColor3f(0.0,0.0,1.0); //blue
	vertex(th2,ph2+DEF_D);
      }
      glEnd();
    }
  }
  /* cylinder */
  else if (objId == 2) {
    /*  sides */
    glBegin(GL_QUAD_STRIP);
    for (j=0;j<=360;j+=DEF_D) {
      glColor3f(1.0,1.0,0.0);
      glVertex3f(Cos(j),+1,Sin(j));
      glColor3f(0.0,1.0,0.0);
      glVertex3f(Cos(j),-1,Sin(j));
    }
    glEnd();

    /* top and bottom circles */
    /* reuse the currentTexture on top and bottom) */
    for (i=1;i>=-1;i-=2) {
      glBegin(GL_TRIANGLE_FAN);
      glColor3f(0.0,0.0,1.0);
      glVertex3f(0,i,0);
      for (k=0;k<=360;k+=DEF_D) {
	glColor3f(1.0,0.0,0.0);
	glVertex3f(i*Cos(k),i,Sin(k));
      }
      glEnd();
    }
  }
  /* cone */
  else if (objId == 3) {
    /* sides */
    glBegin(GL_TRIANGLES);
    for (k=0;k<=360;k+=DEF_D){
      glColor3f(0.0,0.0,1.0);
      glVertex3f(0,0,1);
      glColor3f(0.0,1.0,1.0);
      glVertex3f(Cos(k),Sin(k),0);
      glColor3f(1.0,0.0,0.0);
      glVertex3f(Cos(k+DEF_D),Sin(k+DEF_D),0);
    }
    glEnd();

    /* bottom circle */ 
    /* rotate back */
    glRotated(90,1,0,0);
    glBegin(GL_TRIANGLES);
    for (k=0;k<=360;k+=DEF_D) {
      glColor3f(1.0,0.0,0.0);
      glVertex3f(0,0,0);
      glColor3f(1.0,0.0,1.0);
      glVertex3f(Cos(k),0,Sin(k));
      glColor3f(1.0,1.0,0.0);
      glVertex3f(Cos(k+DEF_D),0,Sin(k+DEF_D));
    }
    glEnd();
  }
  errCheck("error in draw shape");
}

/*
 *  display()
 *  ------
 *  Display the scene
 */
void display()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();

  /* setup functions */
  setEye();

  /* draw */
  drawAxes();
  drawValues();

  /* magic here */
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
  asp = (height>0) ? (double)width/height : 1;
  glViewport(0,0, width,height);
  project();
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
  /*  Spacebar - Toggle through shapes */
  else if (key == 32) {
    if (objId == 3) objId = 0;
    else objId++;
  }
  else if (key == 'a' || key == 'A') toggleAxes = 1-toggleAxes;
  else if (key == 'v' || key == 'V') toggleValues = 1-toggleValues;
  else if (key == 'm' || key == 'M') toggleMode = 1-toggleMode;
  /*  Change field of view angle */
  else if (key == '-' && key>1) fov--;
  else if (key == '+' && key<179) fov++;
  /*  Change dimensions */
  else if (key == 'D') dim += 0.1;
  else if (key == 'd' && dim>1) dim -= 0.1;

  project();
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

  project();
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
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(windowWidth,windowHeight);
  glutCreateWindow(windowName);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(windowKey);
  glutSpecialFunc(windowSpecial);

  glutCreateMenu(windowMenu);
  glutAddMenuEntry("Toggle Axes [a]",'a');
  glutAddMenuEntry("Toggle Values [v]",'v');
  glutAddMenuEntry("Toggle Mode [m]",'m');
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}
