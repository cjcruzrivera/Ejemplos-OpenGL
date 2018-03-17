/* 
 * File:   segunda_tortuga.cpp
 * Author: Camilo José Cruz Rivera 1428907
 * Author: Erik López Pacheco 1430406
 * Author: Jesús Alberto Ramírez Otálvaro 1422554
 *
 * Created on 17 de Marzo de 2018, 16:21
 */
//

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

bool command = false; /* command mode */
char strCommand[256];
bool mostarEjes = false;
GLfloat camaraX = 0.0, camaraY = 1.0, camaraZ = 3.0;

void dibujarEjes()
{

    //Dibujar ejes
    glBegin(GL_LINES);

    //Eje X
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    //Eje Y
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    //Eje Z
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);

    glEnd();
}

void drawTurtle()
{
    GLdouble x[] = {0.0, 1.0, 2.0, 2.0, 2.0, 2.0, 1.0, 2.0, 3.0, 4.0, 5.0, 5.0, 4.0, 2.0, 3.0, 3.0, 3.0, 2.0, 3.0, 4.0, 5.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0};
    GLdouble z[] = {9.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 4.0, 5.0, 5.0, 4.0, 3.0, 2.0, 2.0, 1.0, 0.0, -1.0, -2.0, -2.0, -2.0, -3.0, -4.0, -5.0, -5.0, -4.0, -4.0, -4.0};
    GLint i;
    glColor3f(1.0, 1.0, 0);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < 28; i++)
    {
        glVertex3f(x[i] * 0.15, 0.0, -.15 * z[i]);
    }
    for (i = 26; i >= 1; i--)
    {
        glVertex3f(-.15 * x[i], 0.0, -.15 * z[i]);
    }
    glEnd();
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
    gluLookAt(camaraX, camaraY, camaraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display(void)
{

    glClearColor(.0, .0, .0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (mostarEjes)
    {

        //Función que dibuja los ejes X,Y y Z
        dibujarEjes();
    }

    //Función que dibuja la tortuga con glBegin()
    drawTurtle();

    glutSwapBuffers();
}

void parseCommand(char *strCommandParse)
{
    char *strToken0;
    char *strToken1;
    double val;
    strToken0 = strtok(strCommandParse, " ");
    while ((strToken1 = strtok(NULL, " ")) != NULL)
    {
        val = atof(strToken1);
        if (!strcmp("fd", strToken0))
        { // FORWARD
            glTranslatef(0.0, 0.0, val);
        }
        else if (!strcmp("bk", strToken0))
        { // BACK
            glTranslatef(0.0, 0.0, -val);
        }
        else if (!strcmp("rt", strToken0))
        { // RIGHT
            glRotatef(-val, 0., 1., 0.);
        }
        else if (!strcmp("lt", strToken0))
        { // LEFT
            glRotatef(val, 0., 1., 0.);
        }
        else if (!strcmp("up", strToken0))
        { // UP
            glRotatef(val, 1., 0., 0.);
        }
        else if (!strcmp("dn", strToken0))
        { // DOWN
            glRotatef(-val, 1., 0., 0.);
        }
        else if (!strcmp("rr", strToken0))
        { // RIGHTROLL
            glRotatef(-val, 0., 0., 1.);
        }
        else if (!strcmp("rl", strToken0))
        { // LEFTROLL
            glRotatef(-val, 0., 0., 1.);
        }
        strToken0 = strtok(NULL, " ");
        display();
    }
    // EXIT COMMAND MODE
    if (strToken0 != NULL && strncmp(strToken0, "exit", 4) == 0)
    {
        command = false;
        // HOME
    }
    else if (strToken0 != NULL && !strcmp("home", strToken0))
    {
        glLoadIdentity();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (command)
    {

        if (key == 13)
        {
            cout << strCommand << endl;
            strcat(strCommand, " ");
            if (strlen(strCommand) == 1)
                command = false;
            parseCommand(strCommand);
            strcpy(strCommand, "");
        }
        else
        {
            char strKey[2] = " ";
            strKey[0] = key;
            //printf(strKey);
            strcat(strCommand, strKey);
        }
    }
    else
    {
        switch (key)
        {
        case 'h':
            printf("help\n\n");
            printf("c - Toggle culling\n");
            printf("1 - Rotate in X axis\n");
            printf("2 - Rotate in Y axis\n");
            printf("3 - Rotate in Z axis\n");
            printf("a - Show axes\n");
            printf("u - View from up\n");
            printf("d - View from down\n");
            printf("r - View from right\n");
            printf("l - View from left\n");
            printf("q/escape - Quit\n\n");
            break;
        case 'c':
            if (glIsEnabled(GL_CULL_FACE))
            {
                glDisable(GL_CULL_FACE);
            }
            else
            {
                glEnable(GL_CULL_FACE);
            }
            break;
        case '1':
            glRotatef(1.0, 1., 0., 0.);
            break;
        case '2':
            glRotatef(1.0, 0., 1., 0.);
            break;
        case '3':
            glRotatef(1.0, 0., 0., 1.);
            break;
        case 'a':
            mostarEjes = (mostarEjes) ? false : true;
            break;
        case 'u':
            camaraX = 1.0;
            camaraY = 3.0;
            camaraZ = 0.0;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(camaraX, camaraY, camaraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'd':
            camaraX = -1.0;
            camaraY = -3.0;
            camaraZ = 0.0;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(camaraX, camaraY, camaraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'r':
            camaraX = 3.0;
            camaraY = 0.0;
            camaraZ = 1.0;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(camaraX, camaraY, camaraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'l':
            camaraX = -3.0;
            camaraY = 0.0;
            camaraZ = -1.0;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(camaraX, camaraY, camaraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'q':
        case 27:
            exit(0);
            break;
        case 'i':
            command = true;
            break;
        }
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Practica 2");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}