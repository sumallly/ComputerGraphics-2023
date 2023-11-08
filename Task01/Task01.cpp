// OpenGL_Task01.cpp
// 2023/09/28
// Task_01
// T507
// Ibuki Umehara
//

#include <GL/glut.h>

void display(void);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutCreateWindow("CG_Task01_T507 IbukiUmehara"); //   

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void display(void) {
	glClearColor(0.5,
		0.5, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutWireTeapot(0.5);      // Teapot‚Ì•`‰æ
	glFlush();
}
