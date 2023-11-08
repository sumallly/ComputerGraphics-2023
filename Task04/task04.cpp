// OpenGL_Task04.cpp
// 2022/10/17 �u�`�̓�
// Task_04 �ۑ�ԍ�
// T507 �w�Дԍ�
// Ibuki Umehara ����
//
#include <GL/glut.h>
void resize(int w, int h);
void display(void);
void myAxis(void);
void myObject01(void);
void myObject02(void);
//void myObject03(void);
int viewportWidth, viewportHight;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(600, 400);
	glutCreateWindow("CG_Task04 T507 Ibuki Umehara");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void resize(int w, int h) //w,h �͌��݂̃E�C���h�E�̕��ƍ�������������
{
	viewportWidth = w;
	viewportHight = h;
	// �r���[�|�[�g�ϊ�U
	glViewport(0, 0, w, h); //�E�C���h�E�S�̂ɕ\��
	glClearColor(0.5, 0.5, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	// ���e�ϊ�P
	glMatrixMode(GL_PROJECTION); // ���e�ϊ�P���[�h�ɐؑ�
	glLoadIdentity();
	// �I��: �ȉ�2�̂ǂ��炩��I��
	// 1)�������e // ����p�̂���ʏ���w�n
	gluPerspective(13.0, (double)viewportWidth /
		(double)viewportHight, 0.1, 100.0);
	// 2)���˓��e // �e���Z���g���b�N
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 3.0, 7.0);
}

void display(void)
{
	// ����ϊ�V
	glMatrixMode(GL_MODELVIEW); //���f���ϊ����[�h�̊J�n
	glLoadIdentity(); //�ϊ��s��̏�����
	//gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	gluLookAt(6.0, -6.0, 4.0, 0.0, 0.0, 0.3, 0.0, 0.0, 1.0);
	myObject01();	//Pot
	myObject02();	//Box
	//myObject03();
	myAxis();
	glFlush();
}

void myAxis(void)
{
	glLineWidth(1.0);
	//����

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
	glRotated(90.0, 1.0, 0.0, 0.0); //��]�ړ�
	glTranslatef(0.0, 0.67, 0.0); //���s�ړ�
	glScalef(1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glutWireTeapot(0.5); // Teapot�̕`��
	glPopMatrix();
}

void myObject02(void)
{
	glPushMatrix();
	//���f�����O�ϊ�M
	glScalef(1.0, 1.0, 0.3);
	glTranslatef(0.0, 0.0, 0.5); //���s�ړ�
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(1);
	glPopMatrix();
}