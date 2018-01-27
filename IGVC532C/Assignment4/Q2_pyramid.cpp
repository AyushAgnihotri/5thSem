#include <GL/glut.h>
GLfloat xRotated, yRotated, zRotated;

void DrawCube(void)
{
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	glLoadIdentity();
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.0,0.0,-0.105);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);
    glBegin(GL_QUADS);           // Begin drawing the pyramid with 4 triangles
        // Bottom
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(-0.5f, 0.0f, -0.3f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(0.5f, 0.0f, -0.3f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(0.5f, 0.0f, 0.3f);
      glColor3f(0.0f, 0.3f, 1.0f);     // Blue
      glVertex3f(-0.5f, 0.0f, 0.3f);
    glEnd();  
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f, 0.5f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-0.5f, 0.0f, 0.3f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(0.5f, 0.0f, 0.3f);
    glEnd();
    glBegin(GL_TRIANGLES);
      // Right
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 0.5f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(0.5f, 0.0f, 0.3f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(0.5f, 0.0f, -0.3f);
    glEnd();
    glBegin(GL_TRIANGLES);
      // Left
      glColor3f(1.0f,0.0f,0.0f);       // Red
      glVertex3f( 0.0f, 0.5f, 0.0f);
      glColor3f(0.0f,0.0f,1.0f);       // Blue
      glVertex3f(-0.5f,0.0f,-0.3f);
      glColor3f(0.0f,1.0f,0.0f);       // Green
      glVertex3f(-0.5f,0.0f, 0.3f);
    glEnd();
    glBegin(GL_TRIANGLES);
      // Back
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f, 0.5f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(0.5f, 0.0f, -0.3f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-0.5f, 0.0f, -0.3f);
      
   glEnd();   // Done drawing the pyramid
   glFlush();
}


void animation(void)
{
     yRotated += 0.011;
     xRotated += 0.006;
    // zRotated += 0.01; 
    DrawCube();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[1]);
	glutDisplayFunc(DrawCube);
	glutIdleFunc(animation);
	glutMainLoop();
	return 0;
}