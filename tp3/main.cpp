#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

#define ECHAP 27
#define PI 3.14159265359

int timee = 0;
int timebase = 0;
float angle = 0.0, angle2 = 0.0;
float direction = 0.1;
float x = 0.0;

void window_reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(16.0 * cos(angle), 5, 16.0 * sin(angle),10.0 * cos(angle), 0.0, 10.0 * sin(angle),0,1,0);

	//glTranslatef(angle+=0.01, 0, 0);
	//glutSolidCube(2);

	timee = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
	float dt = float(timee -timebase)/1000.0;// delta time
	timebase = timee;
	
	glPushMatrix();
	glRotatef(angle2, 0.0, -1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(4, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0 * cos(angle), 0.0, 10.0 * sin(angle));

	
	glPushMatrix();
	glRotatef(angle2 * 3, 0.0, -1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidSphere(2, 50, 50);
	glPopMatrix();


	glTranslatef(4.0 * cos(2 * angle), 0.0, 4.0 * sin(2 * angle));
	

	glPushMatrix();
	glRotatef(angle2 * 1.5, 0.0, -1.0, 0.0);
	glColor3f(192.0 / 255.0, 192.0 / 255.0, 192.0 / 255.0);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();

	glPopMatrix();

	

	glPushMatrix();
	glTranslatef(18.0 * cos(angle), 0.0, 18.0 * sin(angle));
	
	glPushMatrix();
	glRotatef(angle2, 0.0, -1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(2, 50, 50);
	glPopMatrix();
	
	glPopMatrix();

	angle += 2*PI/10 * dt;
	angle2 += 360/10 * dt;

	glutSwapBuffers();
	glFlush();
}

void initGL()
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

	glClearColor(0, 0, 0, 1);
}

void window_key(unsigned char key, int x, int y)
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


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("TP 2 : Transformaciones");
	initGL();
	glutDisplayFunc(window_display);
	glutReshapeFunc(window_reshape);
	glutKeyboardFunc(window_key);
	glutIdleFunc(window_display);
	glutMainLoop();

	return 0;
}