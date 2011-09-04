#include <GL/glut.h>
#include <stdlib.h>

GLfloat anguloEsfera = 0.0f;
GLfloat anguloPerspectiva = 60.0f;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
}

void drawHouse(void){
  glColor3f(1.0f, 1.0f, 1); 
  glBegin(GL_QUADS); //cara frontal, blanco
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f( 1.0f, -1.0f, 1.0f);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
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
  glColor3f(1.0f, 1.0f, 1.0f);
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glColor3f (1.0, 1.0, 1.0);
  glLoadIdentity ();             /* clear the matrix */
  /* viewing transformation  */
  gluLookAt (0.0, 0.0, 10.0, 0.0, 0, 0.0, 0.0, 1.0, 0.0);
  
  //glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
  glutWireCube (1.0);   
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
