
#include <GL/glut.h>
#include <iostream>

void triangle()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    int i;
    for(i=1;i<=2400;i++)
    {
        glBegin(GL_LINES);
            glVertex2i(30,30);
            glVertex2i(40,40);
        glEnd();
        glRotated(0.15,0,0,1.0);
        if((i/100)%2==0)
        {
            glColor3f(0.0,0.0,1.0);
        }
        else
        {
            glColor3f(1.0,0.0,0.0);
        }
        glBegin(GL_LINES);
            glVertex2i(0,0);
            glVertex2i(30,30);
        glEnd();
    }
    glRotated(-360,0,0,1.0);
    glColor3f(0.0,0.0,0.0);
    for(i=1;i<=2400;i++)
    {
        glBegin(GL_LINES);
            glVertex2i(0,0);
            glVertex2i(20,20);
        glEnd();
        glRotated(0.15,0,0,1.0);
    }
    glRotated(-360,0,0,1.0);
    glColor3f(0.5,0.5,0.5);
    for(i=1;i<=24;i++)
    {
        glBegin(GL_LINES);
            glVertex2i(0,0);
            glVertex2i(20,20);
        glEnd();
        glRotated(15,0,0,1.0);
    }
    glColor3f(0.0,1.0,0.0);
    for(i=1;i<=2400;i++)
    {
        glBegin(GL_LINES);
            glVertex2i(0,0);
            glVertex2i(10,10);
        glEnd();
        glRotated(0.15,0,0,1.0);
    }
    glRotated(-360,0,0,1.0);
    glColor3f(0.5,0.5,0.5);
    for(i=1;i<=24;i++)
    {
        glBegin(GL_LINES);
            glVertex2i(0,0);
            glVertex2i(20,20);
        glEnd();
        glRotated(45,0,0,1.0);
    }

    glFlush();
}
int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,150);
    glutInitWindowSize(600,600);
    glutCreateWindow("Hey");
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(-100.0,100.0,-100.0,100.0);
    glutDisplayFunc(triangle);
    glutMainLoop();
}
