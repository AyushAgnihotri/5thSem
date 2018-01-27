#include <GL/glut.h>
void XOR() 
{

	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	for(int j=1;j<=2;j++) {
		if(j==2)
		glRotatef(90,0,0,1);
		for(int i=1;i<=2;i++) {
			if(i==1)
				glTranslatef(-0.05,0.3,0);
			if(i==2) 
				glTranslatef(-0.05,-0.3,0);
			glBegin(GL_LINE_LOOP);
				glVertex2f(0,0.10);
				glVertex2f(0,-0.10);
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex2f(-0.10,0);
				glVertex2f(0.25,0);
			glEnd();
			glBegin(GL_TRIANGLES);
				glColor3f(1.0f, 1.0f, 1.0f);    
				glVertex2f(0,0);
				glColor3f(0.0f, 0.0f, 0.0f);    
				glVertex2f(0.10,0.10);
				glColor3f(0.0f, 0.0f, 0.0f);    
				glVertex2f(0.10,-0.10);
			glEnd();
			//glLoadIdentity();
			if(i==1)
				glTranslatef(0.05,-0.3,0);
			if(i==2)
				glTranslatef(0.05,0.3,0);
		}
	}
	glLoadIdentity();
	glFlush();
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(200,200);
	glutCreateWindow("XOR");
	glutDisplayFunc(XOR);
	glutMainLoop();
	return 0;
}