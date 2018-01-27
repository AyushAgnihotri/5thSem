#include <GL/glut.h>
GLfloat xRotated, yRotated, zRotated;

void DrawCube(void)
{
	glClearColor(0,0,0,0);
    glEnable(GL_CULL_FACE);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
   	glLoadIdentity();
        glTranslatef(0.0,0.0,-0.105);
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
  glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(1.0f,1.0f,1.0f);    // Color Blue//upper surface
    glVertex3f( 0.3f, 0.3f,-0.3f);    // Top Right Of The Quad (Top)
    glVertex3f(-0.3f, 0.3f,-0.3f);    // Top Left Of The Quad (Top)
    glVertex3f(-0.3f, 0.3f, 0.3f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 0.3f, 0.3f, 0.3f);    // Bottom Right Of The Quad (Top)
    
    glColor3f(1.0f,0.5f,0.0f);    // Color Orange//Bottom surface
    glVertex3f( 0.3f,-0.3f, 0.3f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-0.3f,-0.3f, 0.3f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-0.3f,-0.3f,-0.3f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 0.3f,-0.3f,-0.3f);    // Bottom Right Of The Quad (Bottom)
    
    glColor3f(1.0f,0.0f,0.0f);    // Color Red    
    glVertex3f( 0.3f, 0.3f, 0.3f);    // Top Right Of The Quad (Front)
    glVertex3f(-0.3f, 0.3f, 0.3f);    // Top Left Of The Quad (Front)
    glVertex3f(-0.3f,-0.3f, 0.3f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 0.3f,-0.3f, 0.3f);    // Bottom Right Of The Quad (Front)
    
    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    glVertex3f( 0.3f,-0.3f,-0.3f);    // Top Right Of The Quad (Back)
    glVertex3f(-0.3f,-0.3f,-0.3f);    // Top Left Of The Quad (Back)
    glVertex3f(-0.3f, 0.3f,-0.3f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 0.3f, 0.3f,-0.3f);    // Bottom Right Of The Quad (Back)
    
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(-0.3f, 0.3f, 0.3f);    // Top Right Of The Quad (Left)
    glVertex3f(-0.3f, 0.3f,-0.3f);    // Top Left Of The Quad (Left)
    glVertex3f(-0.3f,-0.3f,-0.3f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-0.3f,-0.3f, 0.3f);    // Bottom Right Of The Quad (Left)
    
    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glVertex3f( 0.3f, 0.3f,-0.3f);    // Top Right Of The Quad (Right)
    glVertex3f( 0.3f, 0.3f, 0.3f);    // Top Left Of The Quad (Right)
    glVertex3f( 0.3f,-0.3f, 0.3f);    // Bottom Left Of The Quad (Right)
    glVertex3f( 0.3f,-0.3f,-0.3f);    // Bottom Right Of The Quad (Right)
  glEnd();            // End Drawing The Cube
glFlush();
}


void animation(void)
{
     yRotated += 0.01;
     xRotated += 0.02;
     zRotated += 0.01; 
    DrawCube();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	//we initizlilze the glut. functions
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(DrawCube);
	//Set the function for the animation.
	glutIdleFunc(animation);
	glutMainLoop();
	return 0;
}