#include <GL/glut.h> 
void display() {
   glClear(GL_COLOR_BUFFER_BIT);   
   glBegin(GL_QUADS);              
      glColor3f(1.0f, 0.0f, 0.0f); 
      glVertex2f(-0.8f, 0.1f);     
      glVertex2f(-0.2f, 0.1f);     
      glVertex2f(-0.2f, 0.7f);
      glVertex2f(-0.8f, 0.7f);
 
      glColor3f(0.0f, 1.0f, 0.0f); 
      glVertex2f(-0.7f, -0.6f);
      glVertex2f(-0.1f, -0.6f);
      glVertex2f(-0.1f,  0.0f);
      glVertex2f(-0.7f,  0.0f);
 
      glColor3f(0.2f, 0.2f, 0.2f); 
      glVertex2f(-0.9f, -0.7f);
      glColor3f(1.0f, 1.0f, 1.0f); 
      glVertex2f(-0.5f, -0.7f);
      glColor3f(0.2f, 0.2f, 0.2f); 
      glVertex2f(-0.5f, -0.3f);
      glColor3f(1.0f, 1.0f, 1.0f); 
      glVertex2f(-0.9f, -0.3f);
   glEnd();
 
   glBegin(GL_TRIANGLES);          
      glColor3f(0.0f, 0.0f, 1.0f); 
      glVertex2f(0.1f, -0.6f);
      glVertex2f(0.7f, -0.6f);
      glVertex2f(0.4f, -0.1f);
 
      glColor3f(1.0f, 0.0f, 0.0f); 
      glVertex2f(0.3f, -0.4f);
      glColor3f(0.0f, 1.0f, 0.0f); 
      glVertex2f(0.9f, -0.4f);
      glColor3f(0.0f, 0.0f, 1.0f); 
      glVertex2f(0.6f, -0.9f);
   glEnd();
 
   glBegin(GL_POLYGON);            
      glColor3f(1.0f, 1.0f, 0.0f); 
      glVertex2f(0.4f, 0.2f);
      glVertex2f(0.6f, 0.2f);
      glVertex2f(0.7f, 0.4f);
      glVertex2f(0.6f, 0.6f);
      glVertex2f(0.4f, 0.6f);
      glVertex2f(0.3f, 0.4f);
   glEnd();
 
   glFlush();  
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);         
   glutCreateWindow("Lab3Q2");  
   glutInitWindowSize(1300, 1300);   
   glutInitWindowPosition(50, 50); 
   glutDisplayFunc(display);
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                            
   glutMainLoop();                 
   return 0;
}