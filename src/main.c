#include <GL/glut.h>
#include <stdlib.h>
#include "ppmRead.h"

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

GLuint house_wall_texture,house_floor_texture;
GLsizei w,h;
GLubyte *texpat;
GLuint texName[2]; /* array to hold texture names */

int figure = 0;

/**************************************************************************
	Reads in a ppm file (name given in s) and loads it as a texture.
	File should have height and width of a power of 2.  Returns 0
	if error detected, otherwise returns 1
****************************************************************************/
int setTexture(char *s)
{ 
  FILE *fin;
  if ( !(fin = fopen(s, "rb")) )  {  return 0; }
  texpat = readPPM(fin, &w, &h); /* w and h must be a power of 2 */
  if (texpat == NULL) return 0;
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  // Uncomment one of the glTexEnvi lines below
  // (GL_MODULATE is the default)
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
  //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexImage2D( GL_TEXTURE_2D, /* target */ 0, /* level */
  		3, /* components */
  		w, h, /* width, height */ 0, /* border */
  		GL_RGB,  /* format */   GL_UNSIGNED_BYTE, /* type */
  		texpat);
  free(texpat); /* free the texture memory */
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   return 1;
}

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   
   glGenTextures(2, texName); /* make 2 texture names */
   glBindTexture(GL_TEXTURE_2D, texName[0]);
   setTexture("textures/hwood.ppm");
   glBindTexture(GL_TEXTURE_2D, texName[1]);
   setTexture("textures/hfloor.ppm"); 
   
   glEnable(GL_TEXTURE_2D);
   glShadeModel(GL_FLAT);
   upY = 1.0;   
   eyeZ = 10;
}

void drawHouseDoor(){
  glTranslatef(-DOOR_WIDTH/2, 0, 1);

  glRotatef(doorhouseAngle,0,1,0.0f);
  
  if (door_is_opening){
    if (doorhouseAngle < 50)
      doorhouseAngle += 0.02;
    else{
      door_is_opening = 0;
      door_is_open = 1;
    }
  }else{
    if(door_is_closing){
      if (doorhouseAngle > 0)
	doorhouseAngle -= 0.02;
      else{
	door_is_closing = 0;
	door_is_open = 0;
      }
    }
  }

  //glColor3f(170.0f/255, 84.0f/255, 56.0f/255); //coffee color
  //glColor3f(1.0f, 0.0f, 0.0f);

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

void drawTree(void){
  GLUquadric* quad = gluNewQuadric();  
    
  glRotatef(90, 1.0f, 0.0f, 0.0f);
  //  glColor3f(0.0f, 0.0f, 1.0f);
  glColor3f(1.0f, 0.0f, 0.0f);
  gluCylinder(quad,0.5,0.5,3,25,25);//tronco
  
  glTranslatef(0,0,-1.5);
  gluCylinder(quad,0,1,1.5,25,25);          
}

void drawHouse(void){    
  /* Front of the house */
  //glColor3f(0.9f, 0.5f, 0.1);

  glBindTexture(GL_TEXTURE_2D, texName[0]);

  glBegin(GL_QUADS); //front, part 1, to the left of the door
  glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, -1.0f, 1.0f);
  glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0, 1.0); glVertex3f(- DOOR_WIDTH/2, 1.0f, 1.0f);
  glTexCoord2f(1.0, 0.0); glVertex3f(- DOOR_WIDTH/2, -1.0f, 1.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, texName[0]);
  glBegin(GL_QUADS); //front, part 2, to the right of the door
  glTexCoord2f(0.0, 0.0); glVertex3f(1.0f, -1.0f, 1.0f);
  glTexCoord2f(0.0, 1.0); glVertex3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0, 1.0); glVertex3f(DOOR_WIDTH/2, 1.0f, 1.0f);
  glTexCoord2f(1.0, 0.0); glVertex3f(DOOR_WIDTH/2, -1.0f, 1.0f);  
  glEnd();
  glBindTexture(GL_TEXTURE_2D, texName[0]);
  glBegin(GL_QUADS); //front, part 2, above the door
  glTexCoord2f(0.0, 0.0); glVertex3f(-DOOR_WIDTH/2, -1 + DOOR_HEIGHT, 1.0f);
  glTexCoord2f(0.0, 1.0); glVertex3f(-DOOR_WIDTH/2, 1, 1.0f);
  glTexCoord2f(1.0, 1.0); glVertex3f( DOOR_WIDTH/2, 1, 1.0f);
  glTexCoord2f(1.0, 0.0); glVertex3f( DOOR_WIDTH/2, -1 + DOOR_HEIGHT, 1.0f);  
  glEnd();
  //glColor3f(1.0f, 1.0f, 0.0f); 
  glBindTexture(GL_TEXTURE_2D, texName[0]);
  glBegin(GL_QUADS); //cara trasera, amarillo
  glTexCoord2f(0.0, 0.0); glVertex3f( 1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(1.0, 1.0); glVertex3f(-1.0f, 1.0f, -1.0f);
  glTexCoord2f(1.0, 0.0); glVertex3f( 1.0f, 1.0f, -1.0f);
  glEnd();
  //glColor3f(0.0f, 1.0f, 0.0f);
  glBindTexture(GL_TEXTURE_2D, texName[0]);
  glBegin(GL_QUADS); //cara lateral izq, verde
  glTexCoord2f(0.0, 0.0);glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0, 1.0);glVertex3f(-1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0, 1.0);glVertex3f(-1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0, 0.0);glVertex3f(-1.0f, 1.0f, -1.0f);
  glEnd();
  //glColor3f(0.6f, 0.19f, 0.8f);
  glBindTexture(GL_TEXTURE_2D, texName[0]);
  glBegin(GL_QUADS); //cara lateral dcha, morado
  glTexCoord2f(0.0, 0.0);glVertex3f( 1.0f, -1.0f, 1.0f);
  glTexCoord2f(0.0, 1.0);glVertex3f( 1.0f, -1.0f, -1.0f);
  glTexCoord2f(1.0, 1.0);glVertex3f( 1.0f, 1.0f, -1.0f);
  glTexCoord2f(1.0, 0.0);glVertex3f( 1.0f, 1.0f, 1.0f);
  glEnd();
  //glColor3f(0.94f, 0.5f, 0.5f);
  glBindTexture(GL_TEXTURE_2D, texName[0]);
  glBegin(GL_QUADS); //cara arriba, rosado
  glTexCoord2f(0.0, 0.0);glVertex3f(-1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0, 1.0);glVertex3f( 1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0, 1.0);glVertex3f( 1.0f, 1.0f, -1.0f);
  glTexCoord2f(1.0, 0.0);glVertex3f(-1.0f, 1.0f, -1.0f);
  glEnd();
  //glColor3f(0.5f, 1.0f, 0.83f);
  glBindTexture(GL_TEXTURE_2D, texName[1]);
  glBegin(GL_QUADS); //cara abajo, celeste
  glTexCoord2f(0.0, 0.0); glVertex3f( 1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0, 1.0); glVertex3f( 1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0, 1.0); glVertex3f(-1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0, 0.0); glVertex3f(-1.0f, -1.0f, -1.0f);
  glEnd();

  glPushMatrix();
  drawHouseDoor();
  glPopMatrix();
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  //glColor3f (1.0, 1.0, 1.0);  
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
  
  if (!figure)
    drawHouse();
  else
    drawTree();
       
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
  switch (key) {
  case 't':{ //up camera
    if (!figure)
      figure = 1;
    else
      figure = 0;
  } break;
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
  case 'o':{
    system("aplay door.wav &");
    if (!door_is_open)
      door_is_opening = 1;
    else
      door_is_closing = 1;
  }
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
