

#include <GL/glut.h>
#include <stdlib.h>


GLfloat xRot, yRot, zRot, scale;
GLuint object = 0;


struct Point {
	float x;
	float y;
}; 

void drawSierpinski(Point a, Point b, Point c, int level,int colour);


void paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glScalef(scale, scale, scale);

  glRotatef( xRot, 1.0, 0.0, 0.0);
  glRotatef( yRot, 0.0, 1.0, 0.0);
  glRotatef( zRot, 0.0, 0.0, 1.0);

  glCallList(object);
  glFlush();
}

// creates a display list full of OpenGL commands that are executed whenever glCallList is called
GLuint makeObject()
{  
   GLuint list;
   list = glGenLists(1);
   glNewList(list, GL_COMPILE);
     // set the initial color
     //glColor3f( 0.4, 0.3, 0.8 );
     // points for triangle to draw Sierpinski Gasket
     Point a, b, c;
     a.x=0.0; a.y=0.0;
     b.x=250.0; b.y=500.0;
     c.x=500.0; c.y=0.0;

     drawSierpinski(a,b,c,7,0);
   glEndList();
   return list;
} 
void initializeGL()
{
  xRot = yRot = zRot = 0.0;
  scale = 1.25;
  glClearColor( 0.0, 0.0, 0.0, 0.0 ); 
  glEnable( GL_DEPTH_TEST ); 
  object = makeObject(); 
  glShadeModel( GL_SMOOTH ); 
}

void resizeGL( int w, int h )
{
  
  glClearColor (0.0, 0.0, 0.0, 0.0);			
	//glColor3f (0.0, 0.0, 1.0); 					
	glPointSize (3.0);							//set the point size to 3 X 3 pixels

	
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 700.0, 0.0, 700.0);
	glMatrixMode (GL_MODELVIEW);
}




void drawTriangle(Point a, Point b, Point c,int level)
{ 
	if(level==11)  {
	    glColor3f( 0.4, 0.3, 0.8 );}
	    else if(level==12) glColor3f( 0.4, 0.7, 0.5 );
	    else if(level ==131)  glColor3f( 0.4, 0.3, 0.7 );
	    else if(level == 132) glColor3f( 0.4, 0.3, 0.7 );
	    else if(level == 133) glColor3f( 0.4, 0.7, 0.5 );
	    
	else if(level==2)      glColor3f( 0.4, 0.3, 1.0 );
	else      glColor3f( 0.4, 0.7, 0.5 );
	 glBegin(GL_TRIANGLES);
     glVertex2f(a.x,a.y);
     glVertex2f(b.x,b.y);
     glVertex2f(c.x,c.y);
   glEnd();
} 
void drawSierpinski(Point a, Point b, Point c, int level,int colour)
{  
   Point m0, m1, m2;
   if (level > 0) {
     m0.x = (a.x+b.x) /2.0;
     m0.y = (a.y+b.y) /2.0;
     m1.x = (a.x+c.x) /2.0;
     m1.y = (a.y+c.y) /2.0;
     m2.x = (b.x+c.x) /2.0;
     m2.y = (c.y+b.y) /2.0;
     if (colour == 0) {
     drawSierpinski(a,m0,m1,level-1,2);
     drawSierpinski(b,m2,m0,level-1,1);
     drawSierpinski(c,m1,m2,level-1,3);
     }
     else if (colour == 1) {
     	
     	 drawSierpinski(a,m0,m1,level-1,11);
     drawSierpinski(b,m2,m0,level-1,13);
     drawSierpinski(c,m1,m2,level-1,12);
     }
     else if(colour == 13) {
      drawSierpinski(a,m0,m1,level-1,132);
     drawSierpinski(b,m2,m0,level-1,131);
     drawSierpinski(c,m1,m2,level-1,133);
     }
     else {
     	drawSierpinski(a,m0,m1,level-1,colour);
     drawSierpinski(b,m2,m0,level-1,colour);
     drawSierpinski(c,m1,m2,level-1,colour);
     }
   } else drawTriangle(a,b,c,colour);
} 

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutCreateWindow(argv[0]); // this sets the window's title to the name of our executable file
   initializeGL();
   glutDisplayFunc(paintGL);
   glutReshapeFunc(resizeGL);
  
   glutMainLoop();
   return 0;
}
   

