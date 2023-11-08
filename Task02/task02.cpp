// OpenGL_Task02.cpp
// 2023/10/05
// Task_02
// T507
// Ibuki Umehara
//
#include <GL/glut.h>
void display(void);
void myAxis(void);
void myPolygon(void);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("CG_Task02 T507 IbukiUmehara");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void display(void) {

	glClearColor(0.5, 0.5, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0); //ü‚ÌF
	myPolygon();
	myAxis();
	glFlush();
}

void myAxis(void) {

	glLineWidth(1.0); //ü•
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //“h‚è‚Â‚Ô‚µ‚Í GL_FILL
	glBegin(GL_LINES);
	//x²‚Ì•`‰æ
	glColor3f(1.0, 0.0, 0.0); //ü‚ÌF
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.9, 0.0, 0.0);
	//y²‚Ì•`‰æ
	glColor3f(0.0, 1.0, 0.0); //ü‚ÌF
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.9, 0.0);
	//z²‚Ì•`‰æ
	glColor3f(0.0, 0.0, 1.0); //ü‚ÌF
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.9);
	glEnd();

}

void myPolygon(void) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.0, 0.7, 0.0);
	glVertex3f(-0.8, -0.8, 0.0);
	glVertex3f(0.8, -0.8, 0.0);
	glEnd();

}