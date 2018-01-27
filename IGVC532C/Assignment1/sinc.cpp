// sinc function from [-10, 10] with 0.25 step using GL_LINE_STRIP
#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0f);
	glBegin(GL_LINE_STRIP);

	float i, j;

	for(i = -100; i <= 100; i += 0.25) {
		if (i == 0) {
			j = 1;
		} else {
			j = (sin(i))/i;
		}
		glVertex2f(i, j);
	}

	glEnd();
	glFlush();
}

int main(int argv, char	**argc) {
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("sinc function using GL_LINE_STRIP");
	glMatrixMode(GL_PROJECTION);
	//gluOrtho2D(0, 1366, 0, 768);
	gluOrtho2D(-150, 150, -2, 2);  //for zoomed view
	display();
	glutMainLoop();

	return 0;
}
