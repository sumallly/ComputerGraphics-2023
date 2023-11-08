#include <iostream>
#include <math.h>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

void init(void);
void resize(int w, int h);
void display(void);
void idle(void);
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void myAxis(void);

void rotate(double dphi, double dtheta);
void reduce(double* num, double max, double min, double step);
void trans();

void myPolygon01(void);
void myPolygon02(void);
void myPolygon03(void);
void myPolygon04(void);

int viewportWidth, viewportHeight;
double sphereCoord[] = { 5.0, 0.125 * M_PI, 0.25 * M_PI };
double eye[] = { 0.0, 0.0, 0.0 };
double lookat[] = { 0.0, 0.0, 0.1 };
double head[] = { 0.0, 1.0, 0.0 };
double fps = 10.0;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutCreateWindow("CG_Task06 T507 Ibuki Umehara");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	//glutIdleFunc(idle);

	init();

	glutTimerFunc(1000 / fps, timer, 0);
	glutMainLoop();
	return 0;
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // background color
	glClear(GL_COLOR_BUFFER_BIT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void resize(int w, int h)
{
	viewportWidth = w;
	viewportHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 1)?˜?????e // ?????p?????????????w?n
	gluPerspective(10.0, (double)viewportWidth / (double)viewportHeight, 0.1, 100.0);
	// 2)???????e // ?e???Z???g???b?N
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 3.0, 7.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	trans();
	gluLookAt(eye[0], eye[1], eye[2], lookat[0], lookat[1], lookat[2], head[0], head[1], head[2]);

	myPolygon01();
	myPolygon02();
	myPolygon03();
	myPolygon04();
	
	myAxis();

	glFlush();
}

void idle(void)
{
	glutPostRedisplay();
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000/fps, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch ((unsigned char)key) {
	case 'q':
		exit(0);
	default:
		break;
	}
}

void special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	default:
		break;
	}
}

bool PUSHED = FALSE;
int drag[] = { 0, 0 };
void mouse(int button, int state, int x, int y)
{
	drag[0] = x;
	drag[1] = y;

	switch (button) {
	case GLUT_LEFT_BUTTON:
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	case 3: // zoom in
	case 5:	// left + zoom
	case 7: // right + zoom
		if (state)
			sphereCoord[0] /= 1.1;
		break;
	case 4: // zoom out
	case 6:
	case 8:
		if (state)
			sphereCoord[0] *= 1.1;
		break;
	default:
		break;
	}

	switch (state) {
	case 0:
		printf("pushed\n");
		PUSHED = TRUE;
		drag[0] = x;
		drag[1] = y;
		break;
	case 1:
		printf("released\n");
		PUSHED = FALSE;
		break;
	defalut:
		break;
	}

	trans();

	printf("%d, %d, %d, %d \n", button, state, x, y);
}

double kx = 0.1, ky = 0.1;
void motion(int x, int y)
{
	int dx = x - drag[0],
		dy = y - drag[1];
	printf("(%4d, %4d), d(%3d, %3d) \n", x, y, dx, dy);
	rotate((double)dy / 120, (double)dx / 120);
	drag[0] = x;
	drag[1] = y;
}

void rotate(double dphi, double dtheta)
{
	sphereCoord[1] += dphi;
	reduce(&sphereCoord[1], M_PI / 2, -M_PI / 2, M_PI / 180);
	sphereCoord[2] += dtheta;
	reduce(&sphereCoord[2], 2 * M_PI, 0, 2 * M_PI);
}

void reduce(double* num, double max, double min, double step)
{
	if (*num >= max)
		while (*num >= max)
			*num -= step;
	else if (*num < min)
		while (*num < min)
			*num += step;
}

void trans()
{
	// r	 : distance from origin
	// phi	 : angle from xy-plane
	// theta : angle from x-plus-axis on xy-plane
	double r = sphereCoord[0],
		phi = sphereCoord[1],
		theta = sphereCoord[2];
	eye[0] = r * cos(phi) * cos(theta);  // x
	eye[1] = r * sin(phi);               // y
	eye[2] = r * cos(phi) * sin(theta);  // z
}

void myAxis(void)
{
	glLineWidth(1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_LINES);
	//x?????`?? red
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.9, 0.0, 0.0);
	//y?????`?? green
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.9, 0.0);
	//z?????`?? blue
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.9);
	glEnd();

	glFlush();
}

void myPolygon01(void)
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.2);
	glVertex3f(0.0, 0.6, 0.3);
	glVertex3f(0.6, 0.0, 0.3);
	glEnd();
}

void myPolygon02(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.6, 0.0, 0.0);
	glVertex3f(0.0, 0.6, 0.0);
	glEnd();
}

void myPolygon03(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, -0.2);
	glVertex3f(0.6, 0.0, -0.3);
	glVertex3f(0.0, 0.6, -0.3);
	glEnd();
}

void myPolygon04(void)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, -0.4);
	glVertex3f(0.6, 0.0, -0.6);
	glVertex3f(0.0, 0.6, -0.6);
	glEnd();
}