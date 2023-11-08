// OpenGL_Task05.cpp
// 2022/10/24 講義の日
// Task_05 課題番号
// T507 学籍番号
// Ibuki Umehara 氏名
//
#include <stdio.h>
#include <GL/glut.h>
int viewportWidth, viewportHight;
void resize(int w, int h);
void display(void);
void idle(void); // アイドル中の再描画
void motion(int x, int y);
void myAxis(void);
void myObject01(void);
void myObject02(void);
void myObject03(void);
// インターフェース,キーボード,マウス操作
bool flagWire = true;
void keyboard(unsigned char key, int x, int y);
float eye[] = { 5.0, -7.0, 5.0 }; //視点
float head[] = { 0.0, 0.0, 1.0 };
void special(int key, int x, int y);
void mouse(int button, int state, int x, int y); //マウス操作

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("CG_Task05 T507 Ibuki Umehara");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);//キーボードの利用
	glutSpecialFunc(special); //矢印キーなどの特殊キー利用
	glutMouseFunc(mouse); //マウス操作
	glutMotionFunc(motion); //マウス操作
	glutIdleFunc(idle); //再描画
	glClearColor(0.5, 0.5, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
	return 0;
}

void resize(int w, int h) //w,h は現在のウインドウの幅と高さが代入される
{
	viewportWidth = w;
	viewportHight = h;
	// ビューポート変換U
	glViewport(0, 0, w, h); //ウインドウ全体に表示
	// 投影変換P
	glMatrixMode(GL_PROJECTION); // 投影変換P モードに切替
	glLoadIdentity();
	// 選択: 以下2のどちらかを選択
	// 1)透視投影 // 視野角のある通常光学系
	gluPerspective(10.0, (double)viewportWidth / (double)viewportHight, 1.0, 15.0);
	// 2)正射投影 // テレセントリック
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 3.0, 7.0);
}
void display(void) {
	//カラーバッファ,デプスバッファのクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//変更
	// 視野変換V
	glMatrixMode(GL_MODELVIEW); //モデル変換モードの開始
	glLoadIdentity(); //変換行列の初期化
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
	glutPostRedisplay(); //再描画
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
	case GLUT_KEY_RIGHT://x方向
		eye[0] += 0.5;
		break;
	case GLUT_KEY_LEFT://-x方向
		eye[0] -= 0.5;
		break;
	case GLUT_KEY_UP:
		eye[2] += 0.5;//z方向
		break;
	case GLUT_KEY_DOWN:
		eye[2] -= 0.5;//-z方向
		break;

	default:
		break;

	}

}

//マウス操作
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
	//モデリング変換M
	glTranslatef(0.0, 0.0, 0.5); //平行移動
	glRotated((double)90.0 * 1.0, 1.0, 0.0, 0.0); //回転移動
	glScalef(1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0); //線の色
	if (flagWire == true) {
		glutWireTeapot(0.3);
	}
	else {
		glutSolidTeapot(0.3);
	}
	glPopMatrix();
}

void myAxis(void) {
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
void myObject01(void)
{
	glPushMatrix();
	//モデリング変換M
	glTranslatef(0.0, 0.0, 0.0); //平行移動
	glRotated((double)0.0 * 1.0, 1.0, 0.0, 0.0); //回転移動
	glScalef(1.0, 1.0, 1.0);
	myAxis();
	glPopMatrix();
}

void myObject02(void)
{
	glPushMatrix();
	//モデリング変換M
	glScalef(1.0, 1.0, 0.5);
	glTranslatef(0.0, 0.0, 0.25); //平行移動
	glRotated((double)0.0 * 1.0, 0.0, 0.0, 1.0); //回転移動
	glColor3f(0.2, 0.4, 0.2); //線の色
	glutWireCube(0.5);
	glPopMatrix();
}
/*
void myObject03(void)
{
	glPushMatrix();
	//モデリング変換M
	glTranslatef(0.0, 0.0, 0.5); //平行移動
	glRotated((double)90.0 * 1.0, 1.0, 0.0, 0.0); //回転移動
	glScalef(1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0); //線の色
	glutWireTeapot(0.3);
	glPopMatrix();
}
*/
