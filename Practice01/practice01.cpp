//-----------------------------------------------------------
//- OpenGL programming (Step 01)  
//-  Filename: OpenGLtest101.cpp   Date: 11, Oct/2009
//-----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

//Libray
#pragma comment(lib,"opengl32.lib")   //for OpenGL
#pragma comment(lib,"glu32.lib")      //for OpenGL
#pragma comment(lib,"glut32.lib")	//for OpenGL

// ProtoType Statements
void	display(void);

//---------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("OpenGL TEST");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void display(void)
{
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
