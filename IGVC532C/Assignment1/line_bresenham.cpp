// Line drawing using Bresenham Algorithm
#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

void display(float x1, float y1, float x2, float y2) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0f);
	glBegin(GL_POINTS);

	int dx = fabs (x2 - x1), dy = fabs(y2 - y1);
	int p = 2 * dy - dx;
	int a = 2 * dy, b = 2 * (dy - dx);
	int x, y, xend;

	int X1 = (int)(x1 + 0.5);
	int Y1 = (int)(y1 + 0.5);
	int X2 = (int)(x2 + 0.5);
	int Y2 = (int)(y2 + 0.5);	
	 
	if (X1 > X2) {
		x = X2;
		y = Y2;
		xend = X1;
	} else {
		x = X1;
		y = Y1;
		xend = X2;
	}
	glVertex2f(x, y);

	while (x < xend) {
		x++;
		if (p < 0) {
			p += a;
		} else {
			y++;
			p += b;
		}
		glVertex2f(x, y);
	}

	glEnd();
	glFlush();
}

int main(int argv, char **argc) {
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Line drawing using Bresenham Algorithm");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1366, 0, 768);
	//gluOrtho2D(100, 200, 100, 200);  //for zoomed view
	display(100.0, 100.0, 640.0, 450.5);
	//display(5.0, 1.5, 9.3, 7.2);
	glutMainLoop();

	return 0;
}

