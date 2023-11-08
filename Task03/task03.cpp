// OpenGL_Task03.cpp
// 2023/10/12 講義の日
// Task_03 課題番号
// T507 学籍番号
// Ibuki Umehara 氏名
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
	
	// ビューポート変換U
	glViewport(0, 0, 400.0, 400.0);
	
	// 投影変換P
	glMatrixMode(GL_PROJECTION); // 投影変換P モードに切替
	glLoadIdentity();
	
	// 選択: 以下2のどちらかを選択
	// 1)透視投影 // 視野角のある通常光学系
	gluPerspective(130.0, (double)16 / (double)16, 0.1, 100.0);
	// 2)正射投影 // テレセントリック
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	// 視野変換V
	glMatrixMode(GL_MODELVIEW); //モデル変換モードの開始
	glLoadIdentity(); //変換行列の初期化
	gluLookAt(0.0, 0.0, 0.0, 1.0, 0.5, 0.0, 0.0, 1.0, 0.0); // 視野変換V
	
															//モデリング変換M
	glTranslatef(0.0, 0.0, 0.0); //平行移動
	glRotated((double)0 * 1.0, 0.0, 0.0, 1.0); //回転移動
	glScalef(1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glutWireTeapot(0.5); // Teapotの描画
	myAxis();
	glFlush();
}

void myAxis(void)
{

	glLineWidth(1.0); //線幅
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

void resize(int w, int h)
{

	glViewport(0, 0, w, h); //ウインドウ全体に表示
	glMatrixMode(GL_PROJECTION); //投影変換モードへ
	glLoadIdentity(); //投影変換の変換行列を単位行列で初期化
	gluPerspective(25.0, (double)300 / (double)300, 0.8, 2.0);

	//透視投影

	glMatrixMode(GL_MODELVIEW); //視野変換・モデリング変換モードへ
	glLoadIdentity(); //視野変換・モデリング変換の変換行列を単位行列で初期化

}