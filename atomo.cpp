/* 
 * Archivo:   atomo.cpp
 * Camilo José Cruz Rivera 1428907
 * PRIMER PARCIAL PARTE PRACTICA
 * Representación grafica del Sistema Solar
 * Computación Gráfica
 * 
 * 3 de Abril de 2018
 */

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;



void dibujarAtomos(){

	//Dibujar orbitales

	glColor3f(0.0, 0.0, 0.0);

    glPushMatrix();

    glBegin(GL_POINTS);
    for (int i = 3; i < 6; i++)
    {
        float angle = 0.0f;
        while (angle <= (2 * M_PI))
        {
            float x = (float)(((float)i / 8.5) * cos(angle));
            float y = (float)(((float)i / 8.5) * sin(angle));
            glVertex2f(x, y);
            angle += 0.0001;
        }
    }

    glEnd();
    glPopMatrix();


    //dibujar nucleo

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(0.035, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.02, 0.02, 0.0);
    glutSolidSphere(0.035, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.02, 0.04, 0.0);
    glutSolidSphere(0.035, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(-0.025, 0.075, 0.0);
    glutSolidSphere(0.035, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-0.005, -0.005, 0.0);
    glutSolidSphere(0.035, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(-0.01, 0.05, 0.0);
    glutSolidSphere(0.035, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-0.02, -0.04, 0.0);
    glutSolidSphere(0.035, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.025, -0.075, 0.0);
    glutSolidSphere(0.035, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.005, 0.005, 0.0);
    glutSolidSphere(0.035, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.01, -0.05, 0.0);
    glutSolidSphere(0.035, 50.0, 50.0);
    glPopMatrix();

    //dibujar electrones

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glTranslatef(0.48 * cos(M_PI), 0.48 * sin(M_PI), 0.0);
    glutSolidSphere(0.03, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
	glTranslatef(0.48 * cos(M_PI+1), 0.48 * sin(M_PI+1), 0.0);
    glutSolidSphere(0.03, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
glTranslatef(0.48 * cos(M_PI+2), 0.48 * sin(M_PI+2), 0.0);
    glutSolidSphere(0.03, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
glTranslatef(0.48 * cos(M_PI+3), 0.48 * sin(M_PI+3), 0.0);
    glutSolidSphere(0.03, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
glTranslatef(0.48 * cos(M_PI+4), 0.48 * sin(M_PI+4), 0.0);
    glutSolidSphere(0.03, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
glTranslatef(0.48 * cos(M_PI+5), 0.48 * sin(M_PI+5), 0.0);
    glutSolidSphere(0.03, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
glTranslatef(0.48 * cos(M_PI +6 ), 0.48 * sin(M_PI+6), 0.0);
    glutSolidSphere(0.03, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
glTranslatef(0.48 * cos(M_PI+7), 0.48 * sin(M_PI+7), 0.0);
    glutSolidSphere(0.03, 50.0, 50.0);
    glPopMatrix();


 
}


void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

	dibujarAtomos();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'h':
        printf("help\n\n");
        printf("h - to help\n");
        printf("c - cambiar dibujo\n");
        printf("1,2,3 - rotar dibujo\n");
        printf("q/escape - Quit\n\n");
        break;

    case '1':
        glRotatef(5.0, 1., 0., 0.);
        break;
    case '2':
        glRotatef(5.0, 0., 1., 0.);
        break;
    case '3':
        glRotatef(5.0, 0., 0., 1.);
        break;
    case 'q':
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void reshape(int width, int height)
{

    int menor = (width < height) ? width : height;

    glViewport(0, 0, menor, menor);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(750, 700);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Parcial 1. Atomo");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}