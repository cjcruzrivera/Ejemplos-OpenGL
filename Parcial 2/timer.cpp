#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "GL/glut.h"


using namespace std;

GLfloat anguloCuboX = 0.0f;
GLfloat x = 0.0f;
GLfloat y = 0.0f;
bool der = true;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glLoadIdentity();
 
    glColor3f(0,0,0);
    glRotatef(anguloCuboX, 1.0f, 0.0f, 0.0f);
    glTranslatef(x, y, 0.0f);

    glutWireSphere(0.2f, 8, 8);
 
    glFlush();
    glutSwapBuffers();
}

static void Timer(int n){ 
    if(x<1.0f and der){
        anguloCuboX+=0.3f;
        x += 0.1f;
        y += 0.1f;
    }else{
        anguloCuboX+=0.3f;
        x -= 0.1f;
        y -= 0.1f;
    }
    if(x>1.0f){
        der = false;
    }
    if(x<-1.0f){
        der = true;
    }
    glutPostRedisplay();
    glutTimerFunc(n, Timer, n);
}


void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("prueba animacion");

    glClearColor(1,1,1,1);
    glutDisplayFunc(display);
	
    // 100 milliseconds
	Timer(100);
    glutMainLoop();
    
    return 0;
}