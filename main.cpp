/* 
 * Archivo:   main.cpp
 * Camilo José Cruz Rivera 1428907
 * PRIMER PARCIAL PARTE PRACTICA
 * Computación Gráfica
 * 
 * Created on 3 de Abril de 2018
 */
 
#define _USE_MATH_DEFINES
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
#include <math.h>

using namespace std;
int dibujo;

void dibujarEjes()
{

    //Dibuja los ejes

    //Eje x
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 0.0, 0.0);
    glEnd();
    //Eje y
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 30.0, 0.0);
    glEnd();

    //Eje z
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 30.0);
    glEnd();
}

void dibujarMoleculas(void)
{

    //Esfera central
    glColor3f(1.0, 0.8438, 0.0039);
    glutSolidSphere(0.09, 50.0, 50.0);

    //Lineas en Eje z
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.09);
    glColor3f(0.7539, 0.7539, 0.7539);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 0.01, 0.01, 0.3, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.39);
    glColor3f(0.7539, 0.7539, 0.7539);
    GLUquadricObj *obj1 = gluNewQuadric();
    gluCylinder(obj1, 0.01, 0.01, 0.3, 30, 30);
    glPopMatrix();

    //Lineas en Eje x
    glPushMatrix();
    glTranslatef(0.09, 0.0, 0.0);
    glRotatef(90.0, 0., 1., 0.);
    glColor3f(0.7539, 0.7539, 0.7539);
    GLUquadricObj *obj2 = gluNewQuadric();
    gluCylinder(obj1, 0.01, 0.01, 0.3, 30, 30);
    glPopMatrix();

    //Lineas en Eje y
    glPushMatrix();
    glTranslatef(0.0, 0.39, 0.0);
    glRotatef(90.0, 1., 0., 0.);
    glColor3f(0.7539, 0.7539, 0.7539);
    GLUquadricObj *obj3 = gluNewQuadric();
    gluCylinder(obj1, 0.01, 0.01, 0.3, 30, 30);
    glPopMatrix();

    //Esferas eje z
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.39);
    glColor3f(0.5938, 0.7930, 1.0);
    glutSolidSphere(0.09, 50.0, 50.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.3);
    glColor3f(0.5938, 0.7930, 1.0);
    glutSolidSphere(0.09, 50.0, 50.0);
    glPopMatrix();

    //Esfera eje x
    glPushMatrix();
    glTranslatef(0.39, 0.0, 0.0);
    glColor3f(0.5938, 0.7930, 1.0);
    glutSolidSphere(0.09, 50.0, 50.0);
    glPopMatrix();

    //Esfera eje y
    glPushMatrix();
    glTranslatef(0.0, 0.39, 0.0);
    glColor3f(0.5938, 0.7930, 1.0);
    glutSolidSphere(0.09, 50.0, 50.0);
    glPopMatrix();
}

void dibujarPlanetas(void)
{

    //Sol
    glPushMatrix();
    glColor3f(0.9529, 0.6235, 0.0941);
    glutSolidSphere(0.17, 50.0, 50.0);
    glPopMatrix();

    //Mercurio
    glPushMatrix();
    glColor3f(0.5686, 0.6, 0.6235);
    glTranslatef(0.2 * cos(M_PI), 0.2 * sin(M_PI), 0.0);
    glutSolidSphere(0.03, 50.0, 50.0);
    glPopMatrix();

    //Venus
    glPushMatrix();
    glColor3f(0.5469, 0.4922, 0.5117);
    glTranslatef(0.3 * cos(M_PI / 2), 0.3 * sin(M_PI / 2), 0.0);
    glutSolidSphere(0.04, 50.0, 50.0);
    glPopMatrix();

    //Tierra
    glPushMatrix();
    glColor3f(0.0039, 0.0039, 0.5117);
    glTranslatef(0.4 * cos(M_PI / 5), 0.4 * sin(M_PI / 5), 0.0);
    glutSolidSphere(0.06, 50.0, 50.0);
    glPopMatrix();

    //Luna
    glPushMatrix();
    glColor3f(0.5039, 0.5039, 0.5039);
    glTranslatef(0.45 * cos(M_PI / 4), 0.45 * sin(M_PI / 4), 0.01);
    glutSolidSphere(0.009, 50.0, 50.0);
    glPopMatrix();

    //Marte
    glPushMatrix();
    glColor3f(0.808, 0.0039, 0.0039);
    glTranslatef(0.5 * cos((3 * M_PI) / 5), 0.5 * sin((3 * M_PI) / 5), 0.0);
    glutSolidSphere(0.05, 50.0, 50.0);
    glPopMatrix();

    //Júpiter
    glPushMatrix();
    glColor3f(0.8902, 0.8627, 0.7961);
    glTranslatef(0.7 * cos((3 * M_PI) / 2), 0.7 * sin((3 * M_PI) / 2), 0.0);
    glutSolidSphere(0.15, 50.0, 50.0);
    glPopMatrix();

    //Saturno
    glPushMatrix();
    glColor3f(0.8008, 0.8008, 0.5938);
    glTranslatef(0.8 * cos((3 * M_PI) / 4), 0.8 * sin((3 * M_PI) / 4), 0.0);
    glutSolidSphere(0.065, 50.0, 50.0);
    glPopMatrix();

    //Anillos de Saturno

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.8 * cos((3 * M_PI) / 4), 0.8 * sin((3 * M_PI) / 4), 0.0);
    float angle = 0.0f;
    glBegin(GL_POINTS);
    while (angle <= (2 * M_PI))
    {
        float x = (float)(((float)0.9 / 10.0) * cos(angle));
        float y = (float)(((float)0.9 / 10.0) * sin(angle));
        glVertex2f(x, y);
        angle += 0.001;
    }
    glEnd();
    glPopMatrix();

    //Urano
    glPushMatrix();
    glColor3f(0.7930, 0.8945, 0.8945);
    glTranslatef(0.9 * cos(M_PI / 12), 0.9 * sin(M_PI / 12), 0.0);
    glutSolidSphere(0.06, 50.0, 50.0);
    glPopMatrix();

    //Neptuno
    glPushMatrix();
    glColor3f(0.0, 0.1451, 0.4196);
    glTranslatef(1.0 * cos(M_PI / 4), 1.0 * sin(M_PI / 4), 0.0);
    glutSolidSphere(0.05, 50.0, 50.0);
    glPopMatrix();
}

void dibujarOrbitas(void)
{

    glColor3f(1.0, 1.0, 0.6758);

    glPushMatrix();

    glBegin(GL_POINTS);
    for (int i = 2; i < 6; i++)
    {
        float angle = 0.0f;
        while (angle <= (2 * M_PI))
        {
            float x = (float)(((float)i / 10.0) * cos(angle));
            float y = (float)(((float)i / 10.0) * sin(angle));
            glVertex2f(x, y);
            angle += 0.001;
        }
    }

    glEnd();
    glPopMatrix();

    glColor3f(1.0, 1.0, 0.6758);

    glPushMatrix();

    glBegin(GL_POINTS);
    for (int i = 7; i < 11; i++)
    {
        float angle = 0.0f;
        while (angle <= (2 * M_PI))
        {
            float x = (float)(((float)i / 10.0) * cos(angle));
            float y = (float)(((float)i / 10.0) * sin(angle));
            glVertex2f(x, y);
            angle += 0.001;
        }
    }

    glEnd();
    glPopMatrix();
}

void dibujarAsteroides()
{

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    float angle = 0.0f;
    glBegin(GL_POINTS);
    while (angle <= (2 * M_PI))
    {
        float x = (float)(((float)6.0 / 10.0) * cos(angle));
        float y = (float)(((float)6.0 / 10.0) * sin(angle));
        glVertex2f(x, y);
        angle += 0.03;
    }
    glEnd();
    glPopMatrix();
}

void display(void)
{

    if (dibujo == 1)
    {
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        dibujarEjes();
        dibujarMoleculas();
        glFlush();
    }
    else if (dibujo == 2)
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        dibujarEjes();
        dibujarOrbitas();
        dibujarAsteroides();
        dibujarPlanetas();
        glFlush();
    }
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
    case 'c':
        if (dibujo == 1)
        {
            dibujo = 2;
        }
        else if (dibujo == 2)
        {
            dibujo = 1;
        }
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
    gluPerspective(40.0, 1.0, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (dibujo == 1)
    {
        gluLookAt(2.0, 5.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    else
    {
        gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
}

int main(int argc, char **argv)
{
    cout << "Parte practica del primer parcial de computación grafica." << endl;
    cout << "Camilo José Cruz Rivera 1428907 - 3743" << endl
         << endl;
    do
    {
        cout << "Seleccione el dibujo a mostrar" << endl;
        cout << "Ingrese 1 si desea el dibujo de una molecula. " << endl;
        cout << "Ingrese 2 si desea el dibujo del sistema solar. " << endl
             << endl;
        cout << "Para el correcto funcionamiento del sistema ingresar solo los numeros 1 o 2. " << endl;
        cin >> dibujo;

    } while (dibujo != 1 && dibujo != 2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(750, 700);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("PARTE PRACTICA DEL PRIMER PARCIAL");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}