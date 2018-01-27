#include<GL/glut.h>
#include<bits/stdc++.h>
#include<math.h>

void init2D(float r , float g , float b){
	glClearColor(r,g,b,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-4.0,4.0,-4.0,4.0);
}

void drawhelicopter(){
    int i;
    for(i=0;i<360;i++)
    {
        float rad = i*3.1415/180.0;
        glVertex2f(cos(rad)*0.2,sin(rad)*0.1);
    }
    glVertex2f(0.2+cos(30.0*3.1415/180.0)*0.1,sin(30.0*3.1415/180.0)*0.1);
    glVertex2f(0.2+cos(30.0*3.1415/180.0)*0.1,-sin(30.0*3.1415/180.0)*0.1);

}

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glColor3f(1,0,0);
    drawhelicopter();
    glEnd();
    for(int i=0;i<200;i++){
        float x = RandomFloat(-3.5,3.5);
        float y = RandomFloat(-3.5,3.5);
        glTranslatef(x,y,0);    
        glBegin(GL_LINE_LOOP);
        float r = RandomFloat(0.0,1.0);
        float g = RandomFloat(0.0,1.0);
        float b = RandomFloat(0.0,1.0);
        glColor3f(r,g,b);
        drawhelicopter();
        glEnd();
    }         
}

int main(int argc , char *argv[]){	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Helicopter");
	init2D(0.0 , 0.0 , 0.0);
	glutDisplayFunc(display);  
	glutMainLoop();  	
}
