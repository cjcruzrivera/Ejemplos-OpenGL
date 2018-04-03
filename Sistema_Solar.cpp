/* 
 * Archivo:   Sistema_Solar.cpp
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


void dibujarOrbitas(void)
{

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();

    glBegin(GL_POINTS);
    for (int i = 2; i < 6; i++)
    {
        float angle = 0.0f;
        while (angle <= (2 * M_PI))
        {
            float x = (float)(((float)i / 8.5) * cos(angle));
            float y = (float)(((float)i / 8.5) * sin(angle));
            glVertex2f(x, y);
            angle += 0.001;
        }
    }

    glEnd();
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();

    glBegin(GL_POINTS);
    for (int i = 7; i < 11; i++)
    {
        float angle = 0.0f;
        while (angle <= (2 * M_PI))
        {
            float x = (float)(((float)i / 8.5) * cos(angle));
            float y = (float)(((float)i / 8.5) * sin(angle));
            glVertex2f(x, y);
            angle += 0.001;
        }
    }

    glEnd();
    glPopMatrix();
}

void dibujarPlanetas()
{
    //dibujar SOL
    glPushMatrix();
    glColor3f(0.9529, 0.6235, 0.0941);
    glutSolidSphere(0.17, 50.0, 50.0);
    glPopMatrix();

    //dibujar MERCURIO
    glPushMatrix();
    glColor3f(0.65, 0.49, 0.24);
    glTranslatef(0.23 * cos(M_PI), 0.23 * sin(M_PI), 0.0);
    glutSolidSphere(0.03, 50.0, 50.0);
    glPopMatrix();

    //dibujar VENUS
    glPushMatrix();
    glColor3f(0.89, 0.47, 0.20);
    glTranslatef(0.35 * cos(M_PI+(M_PI/7)), 0.35 * sin(M_PI+(M_PI/7)), 0.0);
    glutSolidSphere(0.03, 50.0, 50.0);
    glPopMatrix();

    //dibujar TIERRA
    glPushMatrix();
    glColor3f(0.0, 0.498039, 1.0);
    glTranslatef(0.46 * cos(M_PI+(M_PI/2)), 0.46 * sin(M_PI+(M_PI/2)), 0.0);
    glutSolidSphere(0.06, 50.0, 50.0);
    glPopMatrix();

    //dibujar LUNA
    glPushMatrix();
    glColor3f(0.752941, 0.752941, 0.752941);
    glTranslatef(0.52 * cos(M_PI+(M_PI/2.2)), 0.52 * sin(M_PI+(M_PI/2.2)), 0.0);
    glutSolidSphere(0.01, 50.0, 50.0);
    glPopMatrix();

    //dibujar MARTE
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.585 * cos(2*M_PI), 0.585 * sin(2*M_PI), 0.0);
    glutSolidSphere(0.055, 50.0, 50.0);
    glPopMatrix();


    //dibujar ASTEROIDES
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    float angle = 0.0f;
    glBegin(GL_POINTS);
    while (angle <= (2 * M_PI))
    {
        float x = (float)(((float)6.0 / 8.5) * cos(angle));
        float y = (float)(((float)6.0 / 8.5) * sin(angle));
        glVertex2f(x, y);
        angle += 0.03;
    }
    glEnd();
    glPopMatrix();

    //dibujar JUPITER
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.585 * cos(2*M_PI+2), 0.585 * sin(2*M_PI + 2), 0.0);
    glutSolidSphere(0.055, 50.0, 50.0);
    glPopMatrix();

}


void display(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    dibujarOrbitas();
    dibujarPlanetas();
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
    glutInitWindowSize(950, 900);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Parcial 1. Sistema Solar");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}