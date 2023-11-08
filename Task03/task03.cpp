// OpenGL_Task03.cpp
// 2023/10/12 �u�`�̓�
// Task_03 �ۑ�ԍ�
// T507 �w�Дԍ�
// Ibuki Umehara ����
//
#include <GL/glut.h>
void display(void);
void myAxis(void);
void resize(int w, int h);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(400,400);
	glutCreateWindow("CG_Task03 T507 Umehara");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;
}

void display(void)
{
	glClearColor(0.5, 0.5, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	// �r���[�|�[�g�ϊ�U
	glViewport(0, 0, 400.0, 400.0);
	
	// ���e�ϊ�P
	glMatrixMode(GL_PROJECTION); // ���e�ϊ�P ���[�h�ɐؑ�
	glLoadIdentity();
	
	// �I��: �ȉ�2�̂ǂ��炩��I��
	// 1)�������e // ����p�̂���ʏ���w�n
	gluPerspective(130.0, (double)16 / (double)16, 0.1, 100.0);
	// 2)���˓��e // �e���Z���g���b�N
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	// ����ϊ�V
	glMatrixMode(GL_MODELVIEW); //���f���ϊ����[�h�̊J�n
	glLoadIdentity(); //�ϊ��s��̏�����
	gluLookAt(0.0, 0.0, 0.0, 1.0, 0.5, 0.0, 0.0, 1.0, 0.0); // ����ϊ�V
	
															//���f�����O�ϊ�M
	glTranslatef(0.0, 0.0, 0.0); //���s�ړ�
	glRotated((double)0 * 1.0, 0.0, 0.0, 1.0); //��]�ړ�
	glScalef(1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glutWireTeapot(0.5); // Teapot�̕`��
	myAxis();
	glFlush();
}

void myAxis(void)
{

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

void resize(int w, int h)
{

	glViewport(0, 0, w, h); //�E�C���h�E�S�̂ɕ\��
	glMatrixMode(GL_PROJECTION); //���e�ϊ����[�h��
	glLoadIdentity(); //���e�ϊ��̕ϊ��s���P�ʍs��ŏ�����
	gluPerspective(25.0, (double)300 / (double)300, 0.8, 2.0);

	//�������e

	glMatrixMode(GL_MODELVIEW); //����ϊ��E���f�����O�ϊ����[�h��
	glLoadIdentity(); //����ϊ��E���f�����O�ϊ��̕ϊ��s���P�ʍs��ŏ�����

}