// OpenGL_Task05.cpp
// 2022/10/24 �u�`�̓�
// Task_05 �ۑ�ԍ�
// T507 �w�Дԍ�
// Ibuki Umehara ����
//
#include <stdio.h>
#include <GL/glut.h>
int viewportWidth, viewportHight;
void resize(int w, int h);
void display(void);
void idle(void); // �A�C�h�����̍ĕ`��
void motion(int x, int y);
void myAxis(void);
void myObject01(void);
void myObject02(void);
void myObject03(void);
// �C���^�[�t�F�[�X,�L�[�{�[�h,�}�E�X����
bool flagWire = true;
void keyboard(unsigned char key, int x, int y);
float eye[] = { 5.0, -7.0, 5.0 }; //���_
float head[] = { 0.0, 0.0, 1.0 };
void special(int key, int x, int y);
void mouse(int button, int state, int x, int y); //�}�E�X����

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("CG_Task05 T507 Ibuki Umehara");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);//�L�[�{�[�h�̗��p
	glutSpecialFunc(special); //���L�[�Ȃǂ̓���L�[���p
	glutMouseFunc(mouse); //�}�E�X����
	glutMotionFunc(motion); //�}�E�X����
	glutIdleFunc(idle); //�ĕ`��
	glClearColor(0.5, 0.5, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
	return 0;
}

void resize(int w, int h) //w,h �͌��݂̃E�C���h�E�̕��ƍ�������������
{
	viewportWidth = w;
	viewportHight = h;
	// �r���[�|�[�g�ϊ�U
	glViewport(0, 0, w, h); //�E�C���h�E�S�̂ɕ\��
	// ���e�ϊ�P
	glMatrixMode(GL_PROJECTION); // ���e�ϊ�P ���[�h�ɐؑ�
	glLoadIdentity();
	// �I��: �ȉ�2�̂ǂ��炩��I��
	// 1)�������e // ����p�̂���ʏ���w�n
	gluPerspective(10.0, (double)viewportWidth / (double)viewportHight, 1.0, 15.0);
	// 2)���˓��e // �e���Z���g���b�N
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 3.0, 7.0);
}
void display(void) {
	//�J���[�o�b�t�@,�f�v�X�o�b�t�@�̃N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�ύX
	// ����ϊ�V
	glMatrixMode(GL_MODELVIEW); //���f���ϊ����[�h�̊J�n
	glLoadIdentity(); //�ϊ��s��̏�����
	//gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	gluLookAt(eye[0], eye[1], eye[2], 0.0, 0.0, 0.5, head[0], head[1], head[2]);
	//myAxis();
	myObject01();
	myObject02();
	myObject03();
	glFlush();
}
void idle(void)
{
	glutPostRedisplay(); //�ĕ`��
}

void keyboard(unsigned char key, int x, int y) {
	switch ((unsigned char)key) {
	case 'w':
		flagWire = true;
		break;
	case 's':
		flagWire = false;
		break;
	case 'q':
		exit(0);
		break;
	default:
		break;
	}

}

void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT://x����
		eye[0] += 0.5;
		break;
	case GLUT_KEY_LEFT://-x����
		eye[0] -= 0.5;
		break;
	case GLUT_KEY_UP:
		eye[2] += 0.5;//z����
		break;
	case GLUT_KEY_DOWN:
		eye[2] -= 0.5;//-z����
		break;

	default:
		break;

	}

}

//�}�E�X����
bool PUSHED = FALSE;
int drag[] = { 0,0 };
void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		//printf("LEFT_BUTTON?n");
		eye[0] -= 0.5;
		break;
	case GLUT_RIGHT_BUTTON:
		//printf("RIGHT_BUTTON?n");
		eye[0] += 0.5;
		break;
	case 3: // zoom in
	case 5:
		if (!state)
			printf("zoom in\n");
		break;
	case 4: // zoom out
	case 6:
		if (!state)
			printf("zoom out\n");
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

	printf("%d, %d, %d, %d \n",button, state, x, y);
}

float kx = 0.1;
float ky = 0.1;
void motion(int x, int y) {
	printf("%d, %d \n", x, y);	

	if (PUSHED) {
		eye[0] += -(x - drag[0]) * kx;
		eye[1] += (y - drag[1]) * ky;
		drag[0] = x;
		drag[1] = y;
	}
}

void rotate(int dx, int dy) {

}

void myObject03(void) {
	glPushMatrix();
	//���f�����O�ϊ�M
	glTranslatef(0.0, 0.0, 0.5); //���s�ړ�
	glRotated((double)90.0 * 1.0, 1.0, 0.0, 0.0); //��]�ړ�
	glScalef(1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0); //���̐F
	if (flagWire == true) {
		glutWireTeapot(0.3);
	}
	else {
		glutSolidTeapot(0.3);
	}
	glPopMatrix();
}

void myAxis(void) {
	glLineWidth(1.0); //����
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //�h��Ԃ��� GL_FILL
	glBegin(GL_LINES);
	//x���̕`��
	glColor3f(1.0, 0.0, 0.0); //���̐F
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.9, 0.0, 0.0);
	//y���̕`��
	glColor3f(0.0, 1.0, 0.0); //���̐F
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.9, 0.0);
	//z���̕`��
	glColor3f(0.0, 0.0, 1.0); //���̐F
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.9);
	glEnd();
}
void myObject01(void)
{
	glPushMatrix();
	//���f�����O�ϊ�M
	glTranslatef(0.0, 0.0, 0.0); //���s�ړ�
	glRotated((double)0.0 * 1.0, 1.0, 0.0, 0.0); //��]�ړ�
	glScalef(1.0, 1.0, 1.0);
	myAxis();
	glPopMatrix();
}

void myObject02(void)
{
	glPushMatrix();
	//���f�����O�ϊ�M
	glScalef(1.0, 1.0, 0.5);
	glTranslatef(0.0, 0.0, 0.25); //���s�ړ�
	glRotated((double)0.0 * 1.0, 0.0, 0.0, 1.0); //��]�ړ�
	glColor3f(0.2, 0.4, 0.2); //���̐F
	glutWireCube(0.5);
	glPopMatrix();
}
/*
void myObject03(void)
{
	glPushMatrix();
	//���f�����O�ϊ�M
	glTranslatef(0.0, 0.0, 0.5); //���s�ړ�
	glRotated((double)90.0 * 1.0, 1.0, 0.0, 0.0); //��]�ړ�
	glScalef(1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0); //���̐F
	glutWireTeapot(0.3);
	glPopMatrix();
}
*/
