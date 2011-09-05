#include <GL/glut.h>
#include <stdlib.h>

GLfloat houseAngle = 0.0f;
GLfloat doorhouseAngle = 0.0f;
GLfloat anguloPerspectiva = 60.0f;

GLfloat eyeX,eyeY,eyeZ = 0.0f;
GLfloat centerX,centerY,centerZ = 0.0f;
GLfloat upX,upY,upZ = 0.0f;

GLfloat DOOR_WIDTH = 0.5f;
GLfloat DOOR_HEIGHT = 0.5f;

GLfloat rotate_angle_x = 0.0f;
GLfloat rotate_angle_y = 0.0f;
GLfloat rotate_angle_z = 0.0f;

GLfloat translate_x = 0.0f;
GLfloat translate_y = 0.0f;
GLfloat translate_z = 0.0f;

GLfloat scale_x = 1.0f;
GLfloat scale_y = 1.0f;
GLfloat scale_z = 1.0f;

GLfloat translate_unit = 0.0f;

int unit_sign = 1;

int door_is_opening,door_is_closing,door_is_open;

typedef enum{
  AXIS_Y,
  AXIS_X,
  AXIS_Z
} AXIS_TYPE;

AXIS_TYPE current_axis_type = -1;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   
   upY = 1.0;   
   eyeZ = 10;
}

void drawHouseDoor(){
  glTranslatef(-DOOR_WIDTH/2, 0, 1);

  glRotatef(doorhouseAngle,0,1,0.0f);
  
  if (door_is_opening){
    if (doorhouseAngle < 50)
      doorhouseAngle += 0.05;
    else{
      door_is_opening = 0;
      door_is_open = 1;
    }
  }else{
    if(door_is_closing){
      if (doorhouseAngle > 0)
	doorhouseAngle -= 0.05;
      else{
	door_is_closing = 0;
	door_is_open = 0;
      }
    }
  }

  glColor3f(170.0f/255, 84.0f/255, 56.0f/255); //coffee color
  glBegin(GL_QUADS);
  glVertex3f(0, -1, 0.0f);
  glVertex3f(DOOR_WIDTH, -1, 0.0f);
  glVertex3f(DOOR_WIDTH, -1 + DOOR_HEIGHT, 0.0f);
  glVertex3f(0,-1 + DOOR_HEIGHT, 0.0f);
  glEnd();
}

void openDoor(){
  door_is_opening = 1;
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

  glPushMatrix();
  drawHouseDoor();
  glPopMatrix();
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glColor3f (1.0, 1.0, 1.0);  
  glLoadIdentity ();             /* clear the matrix */
  gluLookAt (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
  /* viewing transformation  */ 
  
  
  //glTranslatef(0,0,0);

  //rotate? 
  //printf("%f, %f, %f\n",translate_x,translate_y,translate_z);
  glTranslatef(translate_x,translate_y,translate_z);
  glScalef (scale_x, scale_y, scale_z);      /* modeling transformation */ 
  glRotatef(rotate_angle_y, 0.0f, 1.0f, 0.0f);  
  glRotatef(rotate_angle_x, 1.0f, 0.0f, 0.0f);
  glRotatef(rotate_angle_z, 0.0f, 0.0f, 1.0f);

//glutWireSphere(1.0f, 25, 25);
  //houseAngle += 0.05f;
  
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
  int mod = glutGetModifiers();
  printf("key: %d\n",key);
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
     centerX += 0.5;
   } break;
   case 'y': {
     if(mod == GLUT_ACTIVE_ALT){ //rotate Y axis{
       rotate_angle_y += unit_sign*0.5;
       printf("ZZA\n");
     }
   }break;
  case 'x': {
    if(mod == GLUT_ACTIVE_ALT) //rotate X axis
      rotate_angle_x += unit_sign*0.5;
  }break;
  case 'z': {
    if(mod == GLUT_ACTIVE_ALT) //rotate Z axis
      rotate_angle_z += unit_sign*0.5;
  }break;
  case 25: { //CTRL + Y
    translate_y += unit_sign*0.5;
  }break;
  case 89: { //SHIFT + Y
    scale_y += unit_sign*0.5;
    if (scale_y + unit_sign*0.5 > 0)
      scale_y += unit_sign*0.5;
  }break;
  case 24: { //CTRL + X
    translate_x += unit_sign*0.5;
  }break;
  case 88: { //SHIFT + X
    scale_x += unit_sign*0.5;
    if (scale_x + unit_sign*0.5 > 0)
      scale_x += unit_sign*0.5;
  }break;
  case 26: { //CTRL + Z
    translate_z += unit_sign*0.5;
  }break;
  case 90: { //SHIFT + Z
    scale_z += unit_sign*0.5;
    if (scale_z + unit_sign*0.5 > 0)
      scale_z += unit_sign*0.5;
  }break;
  case 'o': 
    if (!door_is_open)
      door_is_opening = 1;
    else
      door_is_closing = 1;
    break;
  case 'p': 
    unit_sign = 1;
    break;
  case 'n': 
    unit_sign = -1;
    break;
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
