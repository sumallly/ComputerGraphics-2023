// finaltask.cpp
// 2024/02/07
// FinalTask
// T507
// Ibuki Umehara

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

void myAxisPlus(void);
void rotate(double dphi, double dtheta);
void reduce(double* num, double max, double min, double step);
void move(double depth, double up, double side);
void trans();

void light01();

int viewportWidth, viewportHeight;
double sphereCoord[] = { 5.0, 0.125 * M_PI, 0.25 * M_PI };
double eye[] = { 0.0, 0.0, 0.0 };
double lookat[] = { 0.0, 0.0, 0.0 };
double head[] = { 0.0, 1.0, 0.0 };
double fps = 30.0;


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutCreateWindow("CG_Task00 T507 Ibuki Umehara");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	//glutIdleFunc(idle);

	init();

	glutTimerFunc(1000 / fps, timer, 0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
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

	light01();
}

void resize(int w, int h) {
	viewportWidth = w;
	viewportHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 1)? perspective transformation
	gluPerspective(10.0, (double)viewportWidth / (double)viewportHeight, 0.1, 200.0);
	// 2)? orthographic projection
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 3.0, 7.0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	trans();
	gluLookAt(eye[0], eye[1], eye[2], lookat[0], lookat[1], lookat[2], head[0], head[1], head[2]);

	myAxisPlus();

	glFlush();
}

void idle(void) {
	glutPostRedisplay();
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(1000 / fps, timer, 0);
}

void myAxisPlus(void) {
	bool isEnabledLIGHTING = false;
	if (glIsEnabled(GL_LIGHTING)) {
		isEnabledLIGHTING = true;
		glDisable(GL_LIGHTING);
	}

	glLineWidth(1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_LINES);
	//x-axis red
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.9, 0.0, 0.0);
	//y?-axis green
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.9, 0.0);
	//z?-axis blue
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.9);
	glEnd();

	if (isEnabledLIGHTING)
		glEnable(GL_LIGHTING);

	// ViewPoint Sphere
	glTranslatef(lookat[0], lookat[1], lookat[2]);
	glColor3f(0.5, 0.5, 0.5);
	glutSolidSphere(0.02, 16, 16);

}

void keyboard(unsigned char key, int x, int y) {
	double depth = 0.0, up = 0.0, side = 0.0;
	switch ((unsigned char)key) {
	case 'w': // move to back
		depth += 0.02;
		break;
	case 's': // move to me
		depth -= 0.02;
		break;
	case 'a': // move to left
		side -= 0.02;
		break;
	case 'd': // move to right
		side += 0.02;
		break;
	case 'e': // move to y-plus
		up += 0.02;
		break;
	case 'q': // move to y-minus
		up -= 0.02;
		break;
	case 'o': // exit out
		exit(0);
	default:
		break;
	}
	move(depth, up, side);
	printf("lookat (%f, %f, %f)\n", lookat[0], lookat[1], lookat[2]);
}

void special(int key, int x, int y) {
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
void mouse(int button, int state, int x, int y) {

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
void motion(int x, int y) {
	int dx = x - drag[0],
		dy = y - drag[1];
	printf("(%4d, %4d), d(%3d, %3d) \n", x, y, dx, dy);
	rotate((double)dy / 120, (double)dx / 120);
	drag[0] = x;
	drag[1] = y;
}

// Rotate camera position
void rotate(double dphi, double dtheta) {
	sphereCoord[1] += dphi;
	reduce(&sphereCoord[1], M_PI / 2, -M_PI / 2, M_PI / 180);
	sphereCoord[2] += dtheta;
	reduce(&sphereCoord[2], 2 * M_PI, 0, 2 * M_PI);
}

// Cut to fit the max and min
void reduce(double* num, double max, double min, double step) {
	if (*num >= max)
		while (*num >= max)
			*num -= step;
	else if (*num < min)
		while (*num < min)
			*num += step;
}

// Move viewpoint
void move(double depth, double up, double side) {
	printf("move : %f %f %f\n", depth, up, side);
	double r = sphereCoord[0],
		phi = sphereCoord[1],
		theta = sphereCoord[2];
	lookat[0] -= depth * cos(theta) - side * sin(theta);
	lookat[1] += up * cos(phi) - depth * sin(phi);
	lookat[2] -= depth * sin(theta) + side * cos(theta);
}

// Convert camera position from spherical coordinate to xyz
void trans() {
	// r	 : distance from viewpoint to camera position
	// phi	 : camera position angle from xz-plane
	// theta : camera position angle from x-plus-axis on xz-plane
	double r = sphereCoord[0],
		phi = sphereCoord[1],
		theta = sphereCoord[2];
	eye[0] = lookat[0] + r * cos(phi) * cos(theta);  // x
	eye[1] = lookat[1] + r * sin(phi);               // y
	eye[2] = lookat[2] + r * cos(phi) * sin(theta);  // z
}

void light01(void) {
	// light source
	GLfloat light0_pos[] = { 5.0, -2.0, 10.0, 1.0 }; /* ŒõŒ¹ˆÊ’u */
	GLfloat light0_amb[] = { 0.1, 0.1, 0.1, 0.0 }; /* ŠÂ‹«Œõ‚Ì‹­‚³,F */
	GLfloat light0_dif[] = { 1.0, 1.0, 1.0, 0.0 }; /* ŠgŽUŒõ‚Ì‹­‚³,F */
	GLfloat light0_spc[] = { 0.8, 0.8, 0.8, 0.0 }; /* ‹¾–Ê”½ŽËŒõ‚Ì‹­‚³,F */
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spc);
	//glShadeModel(GL_FLAT); // GL_FLAT or GL_SMOOTH
	glEnable(GL_LIGHTING); //”½ŽË•¨‘Ì‚Ì‚½‚ß‚ÌŒõŒ¹”­Œõ
	glEnable(GL_LIGHT0);
}