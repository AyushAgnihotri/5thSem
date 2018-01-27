// Line drawing using DDA Algorithm (Digital Differential Analyzer)
#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

void display(float x1, float y1, float x2, float y2) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0f);
	glBegin(GL_POINTS);

	int dx = fabs(x2 - x1);
	int dy = fabs(y2 - y1);

	int steps = dx > dy ? dx : dy;

	float xinc = dx / (float) steps;
    float yinc = dy / (float) steps;

	float x = x1;
    float y = y1;

	for (int i = 0; i < steps; i++) {
		glVertex2f((int)(x+0.5), (int)(y+0.5));
		//cout << x << " " << y << endl;
		x += xinc;
		y += yinc;		
	}

	glEnd();
	glFlush();
}

int main(int argv, char	**argc) {
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Line drawing using DDA(Digital Differential Analyzer)");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1366, 0, 768);
	//gluOrtho2D(100, 200, 100, 200);  //for zoomed view
	display(100.0, 100.0, 640.0, 450.5);
	//display(5.0, 1.5, 9.3, 7.2);
	glutMainLoop();

	return 0;
}


