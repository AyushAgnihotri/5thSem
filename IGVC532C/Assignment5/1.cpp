#include <GL/glut.h>
#include <math.h>

#define pi 3.1415
int shx = 2;
GLfloat Result[3][4];
struct Point
{
	GLfloat x, y, z;
};

struct Point p1 = {-35.0, -35.0, 0.0};
struct Point p2 = {-5.0, -35.0, 0.0};
struct Point p3 = {-5.0, -5.0, 0.0};
struct Point p4 = {-35.0, -5.0, 0.0};

void MatrixMultiply(GLfloat m1[3][3], GLfloat m2[3][4])
{
	int r, c;
	GLfloat Temp[3][4];
	for (r = 0; r < 3; r++) {
		for (c = 0; c < 4; c++) {
			Temp[r][c] = m1[r][0] * m2[0][c] + m1[r][1] * m2[1][c] + m1[r][2] * m2[2][c];
		}
	}

	for (r = 0; r < 3; r++) {
		for (c = 0; c < 4; c++) {
			Result[r][c] = Temp[r][c];
		}
	}
}

void square()
{
	/*glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
		glVertex3f(p4.x, p4.y, p4.z);
	glEnd();*/

	GLfloat M[3][4], RF[3][3], RO[3][3], SH[3][3];
	M[0][0] = p1.x; M[0][1] = p2.x; M[0][2] = p3.x; M[0][3] = p4.x;
	M[1][0] = p1.y; M[1][1] = p2.y; M[1][2] = p3.y; M[1][3] = p4.y;
	M[2][0] = p1.z; M[2][1] = p2.z; M[2][2] = p3.z; M[2][3] = p4.z;

	RF[0][0] = 1; RF[0][1] = 0; RF[0][2] = 0;
	RF[1][0] = 0; RF[1][1] = -1; RF[1][2] = 0;
	RF[2][0] = 0; RF[2][1] = 0; RF[2][2] = 1;

	RO[0][0] = cos(45*(pi/180)); RO[0][1] = -sin(45*(pi/180)); RO[0][2] = 0;
	RO[1][0] = sin(45*(pi/180)); RO[1][1] = cos(45*(pi/180)); RO[1][2] = 0;
	RO[2][0] = 0; RO[2][1] = 0; RO[2][2] = 1;

	SH[0][0] = 1; SH[0][1] = shx; SH[0][2] = 0;
	SH[1][0] = 0; SH[1][1] = 1; SH[1][2] = 0;
	SH[2][0] = 0; SH[2][1] = 0; SH[2][2] = 1;
	
	//Reflection in X-axis
	MatrixMultiply(RF, M);

	/*p1.x = Result[0][0]; p1.y = Result[1][0]; p1.z = Result[2][0];
	p2.x = Result[0][1]; p2.y = Result[1][1]; p2.z = Result[2][1];
	p3.x = Result[0][2]; p3.y = Result[1][2]; p3.z = Result[2][2];
	p4.x = Result[0][3]; p4.y = Result[1][3]; p4.z = Result[2][3];	

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
		glVertex3f(p4.x, p4.y, p4.z);
	glEnd();*/

	//Rotation Anticlockwise 45 degrees about center
	MatrixMultiply(RO, Result);

	/*p1.x = Result[0][0]; p1.y = Result[1][0]; p1.z = Result[2][0];
	p2.x = Result[0][1]; p2.y = Result[1][1]; p2.z = Result[2][1];
	p3.x = Result[0][2]; p3.y = Result[1][2]; p3.z = Result[2][2];
	p4.x = Result[0][3]; p4.y = Result[1][3]; p4.z = Result[2][3];	

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
		glVertex3f(p4.x, p4.y, p4.z);
	glEnd();*/

	//Shearing in X-axis by value of 2
	MatrixMultiply(SH, Result);

	p1.x = Result[0][0]; p1.y = Result[1][0]; p1.z = Result[2][0];
	p2.x = Result[0][1]; p2.y = Result[1][1]; p2.z = Result[2][1];
	p3.x = Result[0][2]; p3.y = Result[1][2]; p3.z = Result[2][2];
	p4.x = Result[0][3]; p4.y = Result[1][3]; p4.z = Result[2][3];	

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
		glVertex3f(p4.x, p4.y, p4.z);
	glEnd();

	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lab 5");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(-100, 100, -100, 100);
	glutDisplayFunc(square);
	glutMainLoop();
}