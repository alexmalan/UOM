# ifdef MACOSX
# include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BODIES 20
#define TOP_VIEW 1
#define ECLIPTIC_VIEW 2
#define SHIP_VIEW 3
#define EARTH_VIEW 4
#define PI 3.14159
#define DEG_TO_RAD 0.017453293
#define ORBIT_POLY_SIDES 40
#define TIME_STEP 0.5   

typedef struct
{ 
  char    name[20];       /* name */
  GLfloat r, g, b;        /* colour */
  GLfloat orbital_radius; /* distance to parent body (km) */
  GLfloat orbital_tilt;   /* angle of orbit wrt ecliptic (deg) */
  GLfloat orbital_period; /* time taken to orbit (days) */
  GLfloat radius;         /* radius of body (km) */
  GLfloat axis_tilt;      /* tilt of axis wrt body's orbital plane (deg) */
  GLfloat rot_period;     /* body's period of rotation (days) */
  GLint   orbits_body;    /* identifier of parent body */
  GLfloat spin;           /* current spin value (deg) */
  GLfloat orbit;          /* current orbit value (deg) */
 } body;

body  bodies[MAX_BODIES];
int   numBodies, current_view, draw_labels, draw_orbits, draw_starfield;
float date;
int keyPress;

/*****************************/

float myRand (void)
{
  return (float) rand() / RAND_MAX;
} // myRand

/*****************************/

void drawStarfield (void)
{
  int i= 7000;
  srand(0);
  glBegin (GL_POINTS);

  while(i)
  {
    i = i-1;
    glColor3f(1.0f, 1.0f,1.0f);
    glVertex3f((2* myRand()-1) * 499999999, (2*myRand()-1)*499999999, (2*myRand()-1)*499999999);    
  } // while
  
  glEnd ();
} // drawStarfield

/*****************************/

void drawAxes(void)
{
  if(keyPress == 1)
  {
    glLineWidth(5.0);

    glBegin(GL_LINES);
     glColor3f(1.0,0.0,0.0); // red
         glVertex3f(0.0, 0.0, 0.0);
         glVertex3f(1000000000, 0.0, 0.0);

     glColor3f(0.0,1.0,0.0); // green
         glVertex3f(0.0, 0.0, 0.0);
         glVertex3f(0.0, 1000000000, 0.0);

     glColor3f(0.0,0.0,1.0); // blue
         glVertex3f(0.0, 0.0, 0.0);
         glVertex3f(0.0, 0.0, 1000000000);
     glEnd();

     glLineWidth(1.0);
   } // if
} // drawAxes

/*****************************/

void readSystem(void)
{
  FILE *f;
  int i;
  f = fopen("sys", "r");

  if (f == NULL) 
  {
     printf("The ex2.c was not able to open the 'sys' file\n");
     printf("Use the command:\n");
     printf("  cp /opt/info/courses/COMP27112/ex2/sys .\n");
     exit(0);
  } // if

  fscanf(f, "%d", &numBodies);

  for (i = 0; i < numBodies; i++)
  {
    fscanf(f, "%s %f %f %f %f %f %f %f %f %f %d", 
      bodies[i].name,
      &bodies[i].r, &bodies[i].g, &bodies[i].b,
      &bodies[i].orbital_radius,
      &bodies[i].orbital_tilt,
      &bodies[i].orbital_period,
      &bodies[i].radius,
      &bodies[i].axis_tilt,
      &bodies[i].rot_period,
      &bodies[i].orbits_body);

      bodies[i].spin= 0.0;
      bodies[i].orbit= myRand() * 360.0; 
      bodies[i].radius*= 1000.0; 
  } // for
  fclose(f);
} // readSystem

/*****************************/

void drawString (void *font, float x, float y, char *str) {}

/*****************************/

void setView (void) 
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  switch (current_view) 
  {
    case TOP_VIEW:
      gluLookAt(0.0, 0.5 * 1200000000, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.5);
    break;

    case ECLIPTIC_VIEW:
      gluLookAt(0.0 , 0.0, 0.5* 900000000,
        0.0, 0.0, 0.0,
        0.0, 0.5, 0.0);
    break; 

    case SHIP_VIEW:
      gluLookAt(0.5 * 700000000, 0.5 * 700000000, 0.5 * 700000000,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);  
    break;  

    case EARTH_VIEW: 
      gluLookAt(bodies[3].orbital_radius*sin(bodies[3].orbit *DEG_TO_RAD), 0.5 * 50000000, bodies[3].orbital_radius*cos(bodies[3].orbit *DEG_TO_RAD),
        0.0, 0.0, 0.0,
        0.0, 0.5 *100000000.0, 0.0);
    break;  
  } // switch
} // setView

/*****************************/

void menu (int menuentry) 
{
  switch (menuentry) 
  {
    case 1: current_view= TOP_VIEW;
            break;
    case 2: current_view= ECLIPTIC_VIEW;
            break;
    case 3: current_view= SHIP_VIEW;
            break;
    case 4: current_view= EARTH_VIEW;
            break;
    case 5: draw_labels= !draw_labels;
            break;
    case 6: draw_orbits= !draw_orbits;
            break;
    case 7: draw_starfield= !draw_starfield;
            break;
    case 8: exit(0);
  } // switch
} // menu

/*****************************/

void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutCreateMenu (menu);
  glutAddMenuEntry ("Top view", 1);
  glutAddMenuEntry ("Ecliptic view", 2);
  glutAddMenuEntry ("Spaceship view", 3);
  glutAddMenuEntry ("Earth view", 4);
  glutAddMenuEntry ("", 999);
  glutAddMenuEntry ("Toggle labels", 5);
  glutAddMenuEntry ("Toggle orbits", 6);
  glutAddMenuEntry ("Toggle starfield", 7);
  glutAddMenuEntry ("", 999);
  glutAddMenuEntry ("Quit", 8);
  glutAttachMenu (GLUT_RIGHT_BUTTON);

  current_view= TOP_VIEW;
  draw_labels= 1;
  draw_orbits= 1;
  draw_starfield= 1;
  keyPress = 1;
} // init

/*****************************/

void animate(void)
{
  int i;
  date += TIME_STEP;

  for (i= 0; i < numBodies; i++)  
  {
    bodies[i].spin += 360.0 * TIME_STEP / bodies[i].rot_period;
    bodies[i].orbit += 360.0 * TIME_STEP / bodies[i].orbital_period;
    glutPostRedisplay();
  } // for
} // animate

/*****************************/

void drawOrbit (int n)
{ 
  int index;
  glBegin(GL_LINE_LOOP);
  GLfloat angle = 0.0;
  for( index = 0; index < ORBIT_POLY_SIDES; index++)
  {
    glVertex3f(bodies[n].orbital_radius * cos(angle), 0.0, bodies[n].orbital_radius * sin(angle));
    angle = angle + 2* PI/ORBIT_POLY_SIDES;
  }
  glEnd();
}

/*****************************/

void drawLabel(int n) {}

/*****************************/

void drawBody(int n)
{
  GLint parent = bodies[n].orbits_body;
  bodies[bodies[n].orbits_body].orbital_radius;

  glRotatef(bodies[parent].orbital_tilt, 0.0f, 0.0f, 1.0f);
  glTranslatef(bodies[parent].orbital_radius*sin(bodies[parent].orbit*DEG_TO_RAD), 0.0,bodies[parent].orbital_radius*cos(bodies[parent].orbit
    *DEG_TO_RAD));
  glColor3f(bodies[n].r, bodies[n].g, bodies[n].b);
  glRotatef(bodies[n].orbital_tilt, 0.0f, 0.0f, 1.0f);

  if(draw_orbits)
    drawOrbit(n);

  glRotatef(bodies[n].orbital_tilt, 0.0f, 0.0f, 1.0f);
  glTranslatef(bodies[n].orbital_radius*sin(bodies[n].orbit*DEG_TO_RAD), 0.0, bodies[n].orbital_radius*cos(bodies[n].orbit*DEG_TO_RAD));
  glColor3f(bodies[n].r, bodies[n].g, bodies[n].b);

  glRotatef(bodies[n].orbital_tilt, 0.0f, 0.0f, 1.0f);
  glRotatef(bodies[n].axis_tilt, 1.0f,0.0f, 0.0f);
  glRotatef(bodies[n].spin, 0.0f,1.0f,0.0f);
  glRotatef(90, 1.0f,0.0f, 0.0f);
  
  glColor3f(bodies[n].r, bodies[n].g, bodies[n].b);
  GLint sun_rad = bodies[0].radius;

  glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 2 * bodies[n].radius);
    glVertex3f(0.0, 0.0, -2 * bodies[n].radius);
  glEnd();
  glutWireSphere(bodies[n].radius, 24, 24);

} // drawBody

/*****************************/

void display(void)
{
 int i;

 //if (draw_orbits)
  // drawOrbit(i);
   glClear(GL_COLOR_BUFFER_BIT);
  
  setView();
  drawAxes();

  if (draw_starfield)
    drawStarfield();

  for (i= 0; i < numBodies; i++)
  {
    glPushMatrix(); 
      drawBody (i);
    // drawOrbit(i);
    glPopMatrix();
  } // for

  glutSwapBuffers();
} // display

/*****************************/

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (48.0, (GLfloat) w/(GLfloat) h, 10000.0, 800000000.0);
}
  
/*****************************/

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 27:  
      exit(0);
    case 'x':
      keyPress = 1 - keyPress;
  }
} 

/*****************************/

int main(int argc, char** argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow ("COMP27112 Exercise 2");
  glutFullScreen();
  init ();
  glutDisplayFunc (display); 
  glutReshapeFunc (reshape);
  glutKeyboardFunc (keyboard);
  glutIdleFunc (animate);
  readSystem();
  glutMainLoop ();

  return 0;
} // main method

