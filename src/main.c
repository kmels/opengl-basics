#include <GL/glut.h>
#include <stdlib.h>

GLfloat anguloEsfera = 0.0f;
GLfloat anguloPerspectiva = 60.0f;

GLfloat eyeX,eyeY,eyeZ = 0.0f;
GLfloat centerX,centerY,centerZ = 0.0f;
GLfloat upX,upY,upZ = 0.0f;

GLfloat DOOR_WIDTH = 0.5f;
GLfloat DOOR_HEIGHT = 0.5f;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   
   upY = 1.0;   
   eyeZ = 10;
}

void drawHouseDoor(){    
  glColor3f(170.0f/255, 84.0f/255, 56.0f/255); //coffee color
  glBegin(GL_QUADS); 
  glVertex3f(-DOOR_WIDTH/2, -1, 1.0f);
  glVertex3f( DOOR_WIDTH/2, -1, 1.0f);
  glVertex3f( DOOR_WIDTH/2, -1 + DOOR_HEIGHT, 1.0f);
  glVertex3f( -DOOR_WIDTH/2,-1 + DOOR_HEIGHT, 1.0f);
  glEnd();
}

void drawHouse(void){
  
  
  /* Front of the house */
  glColor3f(1.0f, 1.0f, 1);  
  glBegin(GL_QUADS); //front, part 1, to the left of the door
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(- DOOR_WIDTH/2, 1.0f, 1.0f);
  glVertex3f(- DOOR_WIDTH/2, -1.0f, 1.0f);  
  glEnd();
  glBegin(GL_QUADS); //front, part 2, to the right of the door
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(DOOR_WIDTH/2, 1.0f, 1.0f);
  glVertex3f(DOOR_WIDTH/2, -1.0f, 1.0f);  
  glEnd();
  glBegin(GL_QUADS); //front, part 2, above the door
  glVertex3f(-DOOR_WIDTH/2, -1 + DOOR_HEIGHT, 1.0f);
  glVertex3f(-DOOR_WIDTH/2, 1, 1.0f);
  glVertex3f( DOOR_WIDTH/2, 1, 1.0f);
  glVertex3f( DOOR_WIDTH/2, -1 + DOOR_HEIGHT, 1.0f);  
  glEnd();

  glColor3f(1.0f, 1.0f, 0.0f); 
  glBegin(GL_QUADS); //cara trasera, amarillo
  glVertex3f( 1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f( 1.0f, 1.0f, -1.0f);
  glEnd();
  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS); //cara lateral izq, verde
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glEnd();
  glColor3f(0.6f, 0.19f, 0.8f);
  glBegin(GL_QUADS); //cara lateral dcha, morado
  glVertex3f( 1.0f, -1.0f, 1.0f);
  glVertex3f( 1.0f, -1.0f, -1.0f);
  glVertex3f( 1.0f, 1.0f, -1.0f);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glEnd();
  glColor3f(0.94f, 0.5f, 0.5f);
  glBegin(GL_QUADS); //cara arriba, rosado
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glVertex3f( 1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glEnd();
  glColor3f(0.5f, 1.0f, 0.83f);
  glBegin(GL_QUADS); //cara abajo, celeste
  glVertex3f( 1.0f, -1.0f, -1.0f);
  glVertex3f( 1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glEnd(); 

  drawHouseDoor();
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glColor3f (1.0, 1.0, 1.0);
  glLoadIdentity ();             /* clear the matrix */
  /* viewing transformation  */
  gluLookAt (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
  
  //glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
  //glTranslatef(0,0,0);
  glRotatef(anguloEsfera, 0.0f, 1.0f, 0.0f);
  //glutWireSphere(1.0f, 25, 25);
  anguloEsfera += 0.05f;
  
  drawHouse();  
       
  glFlush ();
  glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(anguloPerspectiva,(GLfloat)w/(GLfloat)h,1.0f,40.0f);
   //glOrtho(-4, 4, -4, 4, 1, 10);
   //glFrustum (-1.0, 1.0, -1.0, 1.0, 5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case '8':{ //up camera
     eyeY += 0.5;
     upY += 0.5;
     centerY += 0.5;     
   } break;
   case '2':{ //down camera
     eyeY -= 0.5;
     centerY -= 0.5;
   } break;
   case '4':{ //left camera
     eyeX -= 0.5;
     upX -= 0.5;
     centerX -= 0.5;
   } break;
   case '5':{ //zoom
     eyeZ -= 0.5;
     centerZ -= 0.5;
   } break;
   case '0':{ //unzoom
     eyeZ += 0.5;
     centerZ += 0.5;
   } break;
   case '6':{ //right camera
     eyeX += 0.5;
     upX += 0.5;
     centerX += 0.5;
   } break;
   case 'i':
     anguloPerspectiva += 3.0f;
     if (anguloPerspectiva > 359)
       anguloPerspectiva = 0;
     break;
   case 'd':
     anguloPerspectiva -= 3.0f;
     if (anguloPerspectiva > 359)
       anguloPerspectiva = 0;
     break;
   case 27:
     exit(0);
     break;
   }
}

void idle(){
  display();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutIdleFunc(idle);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
