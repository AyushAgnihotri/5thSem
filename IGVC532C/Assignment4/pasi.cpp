#include <GL/glut.h>
#include <math.h>

void roulette_wheel()
{
	int i, num_of_triangles = 42;
	float r = 0.2f;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	
	//Outer red/blue circle
	for (i = 0; i <= 360; i += 15) {
		if (i % 2 == 0) {
			glColor3f(0.0, 0.0, 1.0);
		} else {
			glColor3f(1.0, 0.0, 0.0);
		}
		glBegin(GL_POLYGON); // can also use GL_TRIANGLE_FAN
			glVertex2f(0.0, 0.0);
			glVertex2f(0.7, 0.0);
			glVertex2f(0.676, 0.19);
		glEnd();
		glLoadIdentity();
		glRotatef(i, 0.0, 0.0, 1.0);
	}

	//Inner black circle
	for (i = 0; i <= 360; i += 15) {
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON); // can also use GL_TRIANGLE_FAN
			glVertex2f(0.0, 0.0);
			glVertex2f(0.5, 0.0);
			glVertex2f(0.485, 0.13);
		glEnd();
		glLoadIdentity();
		glRotatef(i, 0.0, 0.0, 1.0);
	}

	//Gray lines for black circle
	for (i = 0; i <= 360; i += 15) {
		glColor3f(0.4, 0.4, 0.4);
		glPointSize(5.0);
		glBegin(GL_LINES);
			glVertex2f(0.0, 0.0);
			glVertex2f(0.5, 0.0);
		glEnd();
		glLoadIdentity();
		glRotatef(i, 0.0, 0.0, 1.0);
	}

	//Inner Green circle
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0, 1.0, 0.0);
		for (i = 0; i < num_of_triangles; i++) {
			float theta = (2.0f * M_PI * float(i)) / float(num_of_triangles);
			float x = r * cosf(theta);
			float y = r * sinf(theta);
			glVertex2f(x, y);
		}
	glEnd();


	//Gray lines for Inner green circle
	for (i = 0; i <= 360; i += 45) {
		glPointSize(5.0);
		glBegin(GL_LINES);
			glColor3f(0.4, 0.4, 0.4);
			glVertex2f(0.0, 0.0);
			glColor3f(0.5, 0.6, 0.6);
			glVertex2f(0.5, 0.0);
		glEnd();
		glLoadIdentity();
		glRotatef(i, 0.0, 0.0, 1.0);
	}

	//Red dot in center
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 0.0, 0.0);
		for (i = 0; i < num_of_triangles; i++) {
			float theta = (2.0f * M_PI * float(i)) / float(num_of_triangles);
			float x = 0.02 * cosf(theta);
			float y = 0.02 * sinf(theta);
			glVertex2f(x, y);
		}
	glEnd();

	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Roulette Wheel");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutDisplayFunc(roulette_wheel);
	glutMainLoop();
}