// OpenGL_Task04.cpp
// 2022/10/17 講義の日
// Task_04 課題番号
// T507 学籍番号
// Ibuki Umehara 氏名
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

void resize(int w, int h) //w,h は現在のウインドウの幅と高さが代入される
{
	viewportWidth = w;
	viewportHight = h;
	// ビューポート変換U
	glViewport(0, 0, w, h); //ウインドウ全体に表示
	glClearColor(0.5, 0.5, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	// 投影変換P
	glMatrixMode(GL_PROJECTION); // 投影変換Pモードに切替
	glLoadIdentity();
	// 選択: 以下2のどちらかを選択
	// 1)透視投影 // 視野角のある通常光学系
	gluPerspective(13.0, (double)viewportWidth /
		(double)viewportHight, 0.1, 100.0);
	// 2)正射投影 // テレセントリック
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 3.0, 7.0);
}

void display(void)
{
	// 視野変換V
	glMatrixMode(GL_MODELVIEW); //モデル変換モードの開始
	glLoadIdentity(); //変換行列の初期化
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
	//線幅

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //塗りつぶしは GL_FILL
	glBegin(GL_LINES);
	//x軸の描画
	glColor3f(1.0, 0.0, 0.0); //線の色
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.9, 0.0, 0.0);
	//y軸の描画
	glColor3f(0.0, 1.0, 0.0); //線の色
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.9, 0.0);
	//z軸の描画
	glColor3f(0.0, 0.0, 1.0); //線の色
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.9);
	glEnd();
}

void myObject01(void)
{
	glPushMatrix();
	//モデリング変換M
	glRotated(90.0, 1.0, 0.0, 0.0); //回転移動
	glTranslatef(0.0, 0.67, 0.0); //平行移動
	glScalef(1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glutWireTeapot(0.5); // Teapotの描画
	glPopMatrix();
}

void myObject02(void)
{
	glPushMatrix();
	//モデリング変換M
	glScalef(1.0, 1.0, 0.3);
	glTranslatef(0.0, 0.0, 0.5); //平行移動
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(1);
	glPopMatrix();
}