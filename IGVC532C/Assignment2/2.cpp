#include <GL/glut.h>
void Flower() 
{
	glClear(GL_COLOR_BUFFER_BIT );
	glColor3f(0,0,1.0);
	glBegin(GL_LINES);
		glVertex2f(0.0,0.0);
		glVertex2f(0,-0.8);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(0,-0.8);
		glVertex2f(0.03,-0.77);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(0,-0.8);
		glVertex2f(-0.03,-0.77);
	glEnd();
	for(float i=0;i<36;i++) {
		glBegin(GL_LINE_LOOP);
			glVertex2f(0.0,0.0);
			glVertex2f(0.1,0.1732);
			glVertex2f(0.0,0.3462);
			glVertex2f(-0.1,0.1732);
		glEnd();
		glRotatef(10,0,0,1);
	}
	glLoadIdentity();
	glFlush();
}
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900,900);
	glutInitWindowPosition(200,200);
	glutCreateWindow("Flower");
	glClearColor(1.0,1.0,1.0,0);
	glutDisplayFunc(Flower);
	glutMainLoop();
	return 0;
}