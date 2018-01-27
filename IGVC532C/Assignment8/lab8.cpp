#include <GL/glut.h>
#include <bits/stdc++.h>

void init2D(float r , float g , float b){
	glClearColor(r,g,b,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-5.0,5.0,-5.0,5.0);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	float tri[3][3]={{0,0,0},{1.0,0,0},{0.5,0.86602,0}};
	glTranslatef(-3.0,0,0);
	/*glBegin(GL_LINES);
		glVertex3f(-5.0,0.0,0.0);
		glVertex3f(5.0,0.0,0.0);
		glVertex3f(0.0,5.0,0.0);
		glVertex3f(0.0,-5.0,0.0);
	glEnd();
	*/
	for(int i=0;i<4;i++){
		glColor3f(1,1,1);
        glBegin(GL_LINE_LOOP);
        glVertex3fv(tri[0]);
        glVertex3fv(tri[1]);
        glVertex3fv(tri[2]);
        glEnd();
        glRotatef(90,0,0,1);
   		glTranslatef(-1.0,0,0);
    }

    glTranslatef(3.0,0,0);
    //glPushMatrix();
	glRotatef(-15,1,0,0);
    glRotatef(25,0,1,0);
	glRotatef(-90,1,0,0);

    for(int i=0;i<4;i++){
    	glColor3f(0,1,0);
        glRotatef(125,1,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex3fv(tri[0]);
        glVertex3fv(tri[1]);
        glVertex3fv(tri[2]);
        glEnd();
        glRotatef(-125,1,0,0);
        glRotatef(90,0,0,1);
        glTranslatef(-1.0,0,0);
    }

    //glRotatef(90,1,0,0);
    //glPopMatrix();
    //glTranslatef(1.0,0,0);
	glFlush();
}

int main(int argc , char *argv[]){
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Pyramid");
	init2D(0.0 , 0.0 , 0.0);
	glutDisplayFunc(display);  
	glutMainLoop();  	
}
