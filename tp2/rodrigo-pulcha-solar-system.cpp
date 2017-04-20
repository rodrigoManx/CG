#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1
#define PI 3.14159265359
#define ECHAP 27


int timee = 0;
int timebase = 0;

float angle = 0, radio = 10, x = 0, angle2 = 0;
float direction = 0.1;

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//function called on each frame
GLvoid window_idle();

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 2 : Transformaciones");


	initGL();
	init_scene();


	glutDisplayFunc(&window_display);

	glutReshapeFunc(&window_reshape);

	glutKeyboardFunc(&window_key);

	//function called on each frame
	glutIdleFunc(&window_display);

	glutMainLoop();

	return 1;
}



GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);

	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);
}



GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);


	/*dibujar aqui*/


	
	timee = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
	float dt = float(timee -timebase)/1000.0;// delta time
	timebase = timee;

	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(angle2, 0.0, 0.0, 1.0);
	glutSolidSphere(4, 50, 50);
	glPopMatrix();


	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(10.0 * cos(angle), 10.0 * sin(angle), 0.0);
	
	glPushMatrix();
	glRotatef(angle2 * 3, 0.0, 0.0, 1.0);
	glutSolidSphere(2, 50, 50);
	glPopMatrix();


	
	glColor3f(192.0 / 255.0, 192.0 / 255.0, 192.0 / 255.0);
	glTranslatef(4.0 * cos(2 * angle), 4.0 * sin(2 * angle), 0.0);

	glPushMatrix();
	glRotatef(angle2 * 1.5, 0.0, 0.0, 1.0);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();

	glPopMatrix();

	glColor3f(1.0, 0.0, 0.0);
	
	glPushMatrix();
	glTranslatef(18.0 * cos(angle), 18.0 * sin(angle), 0.0);

	
	glPushMatrix();
	glRotatef(angle2, 0.0, 0.0, 1.0);
	glutSolidSphere(2, 50, 50);
	glPopMatrix();
	
	glPopMatrix();

	angle += 2*PI/60 * dt;
	angle2 += 360/10 * dt;



	/*if (x <= -8 ||  x >= 8) direction *= -1;

	glTranslatef(x += direction, 0, 0);
	glColor3f(1.0,1.0,0.0);
	glutSolidSphere(1, 100, 100);

	
	glPushMatrix();
	glRotatef(angle,0.0,0.0,1.0);
	glTranslatef(radio, 0, 0);
	glutSolidTeapot(1.0);
	glRotatef(angle2,0.0,1.0,0.0);
	glTranslatef(0, 0, 3);
	glutSolidTorus(0.5,1,10,50);
	glPopMatrix();


	glPushMatrix();
	glRotatef(angle, 1.0, 0.0, 0.0);
	glTranslatef(0, 0, radio);
	glutSolidCube(2);
	glPopMatrix();
	//angle = angle + 0.1;
*/
	




	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}


//function called on each frame
GLvoid window_idle()
{
	while(angle < 2*PI)
		angle = angle + 0.1;
	glutPostRedisplay();
}
