#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <fstream>

using namespace std;
#define KEY_ESC 27
#define PI 3.14159265359

bool _direction = true;
//dibuja un simple gizmo

float firstCenterX, firstCenterY, firstSideSize, 
	   secondCenterX, secondCenterY, secondRadio,
	   thirdCenterX, thirdCenterY, thirdRadio, thirdReduction,
	   fourthCenterX, fourthCenterY, fourthRadio, fourthReduction;
int thirdAmount, fourthAmount;

double fourthAngle = PI;

void displayGizmo()
{

	glColor3f(1.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(firstCenterX - (firstSideSize / 2.0), firstCenterY - (firstSideSize / 2.0), 0.0);
    glVertex3f(firstCenterX + (firstSideSize / 2.0), firstCenterY - (firstSideSize / 2.0), 0.0);
    glVertex3f(firstCenterX + (firstSideSize / 2.0), firstCenterY + (firstSideSize / 2.0), 0.0);
    glVertex3f(firstCenterX - (firstSideSize / 2.0), firstCenterY + (firstSideSize / 2.0), 0.0);
    glEnd();




	glColor3f(1.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
    for(double angle = 0; angle < 2*PI; angle += 0.1)
    {
        glVertex3f(secondRadio * cos(angle) + secondCenterX, secondRadio * sin(angle) + secondCenterY, 0.0);
    }
    glEnd();


    float tr = thirdRadio;
    float txc = thirdCenterX; 
    for(int x = thirdAmount; x > 0; x--, tr -= thirdReduction, txc -= thirdReduction){
        glColor3f(1.0,1.0,0.0);
        glBegin(GL_LINE_LOOP);
        for(double angle = 0; angle < 2*PI; angle += 0.1)
        {
            glVertex3f(tr * cos(angle) + txc, tr * sin(angle) + thirdCenterY, 0.0);
        }
        glEnd();
    }

	
	int _oldRad;
	float xc , yc, r;
	xc = fourthCenterX;
	yc = fourthCenterY;
	r = fourthRadio;
    for(int x = fourthAmount; x > 0; x--, r = r * (1 - fourthReduction), 
    	xc = xc + (r + _oldRad) * cos(fourthAngle), 
    	yc = yc + (r + _oldRad) * sin(fourthAngle))
    {
    	_oldRad = r;
    	glColor3f(1.0,1.0,0.0);
    	glBegin(GL_LINE_LOOP);
    	for(double angle = 0; angle < 2*PI; angle += 0.1)
    	{
        	glVertex3f(r * cos(angle) + xc, r * sin(angle) + yc, 0.0);
    	}
    	glEnd();
	}
}

//
//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();


	//dibuja el gizmo
	displayGizmo();

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}


void idle()
{
	if (_direction)
	{
		fourthAngle += 0.1;
		if (fourthAngle >= 2*PI)
		{
			_direction = false;
		}
	}
	else
	{
		fourthAngle -= 0.1;
		if (fourthAngle <= PI)
		{
			_direction = true;
		}	
	}
	//sleep(1);
	glutPostRedisplay(); 
}


//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-100.0f,  100.0f,-100.0f, 100.0f, -1.0f, 1.0f);
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP1 OpenGL : hello_world_OpenGL"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL


	printf("first exercise data\n");
	printf("center x\n");
	cin >> firstCenterX;
	printf("center y\n");
	cin >> firstCenterY;
	printf("side size \n");
	cin >> firstSideSize;
	printf("second exercise data\n");
	printf("center x\n");
	cin >> secondCenterX;
	printf("center y\n");
	cin >> secondCenterY;
	printf("radio\n");
	cin >> secondRadio;
	printf("third exercise data\n");
	printf("center x\n");
	cin >> thirdCenterX;
	printf("center y\n");
	cin >> thirdCenterY;
	printf("radio\n");
	cin >> thirdRadio;
	printf("reduction\n");
	cin >> thirdReduction;
	printf("amount\n");
	cin >> thirdAmount;
	printf("fourth fifth exercise data\n");
	printf("center x\n");
	cin >> fourthCenterX;
	printf("center y\n");
	cin >> fourthCenterY;
	printf("radio\n");
	cin >> fourthRadio;
	printf("reduction\n");
	cin >> fourthReduction;
	printf("amount\n");
	cin >> fourthAmount;
	



	glutIdleFunc(&idle);
	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}