/* 
 * File:   inicio_tortuga.cpp
 * Author: Camilo José Cruz Rivera 1428907
 * Author: Erik López Pacheco 1430406
 * Author: Jesús Alberto Ramírez Otálvaro 1422554
 *
 * Created on 27 de febrero de 2018, 13:21
 */
//
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <stdlib.h>

bool mostarEjes = false, mostrarTortuga = false, tortugaEsferica = false, toroide = true;
GLfloat camaraX = 0.0, camaraY = 1.0, camaraZ = 3.0;

void dibujarEjes(){ 
    
    //Dibujar ejes
    glBegin(GL_LINES);

        //Eje X
        glColor3f(1.0,0.0,0.0);
        glVertex3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);

        //Eje Y
        glColor3f(0.0,1.0,0.0);
        glVertex3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);

        //Eje Z
        glColor3f(0.0,0.0,1.0);
        glVertex3f(0.0f, 0.0f, -1.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);

    glEnd();    

}

void drawTurtle(){  
        
    GLdouble x[] = { 0.0, 1.0, 2.0, 2.0, 2.0, 2.0, 1.0, 2.0, 3.0, 4.0, 5.0, 5.0, 4.0, 2.0, 3.0, 3.0,  3.0,  2.0,  3.0,  4.0,  5.0,  5.0,  4.0,  3.0,  2.0,  1.0,  0.0};
    GLdouble z[] = { 9.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 4.0, 5.0, 5.0, 4.0, 3.0, 2.0, 2.0, 1.0, 0.0, -1.0, -2.0, -2.0, -2.0, -3.0, -4.0, -5.0, -5.0, -4.0, -4.0, -4.0};
    GLint i;
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    for (i=0;i<28;i++){
        glVertex3f(x[i]*0.15,0.0,-.15*z[i]);
    }
    for (i=26;i>=0;i--){
        glVertex3f(-.15*x[i],0.0,-.15*z[i]);
    }
    glEnd();    

}

void drawSphereTurtle(){
        
    GLdouble valx[] = { 0.0, 4.0, -8.0, 0.0, 8.0,-4.0};
    GLdouble valz[] = { -6.0, 2.0, 0.0, 8.0, 0.0,-4.0};
    GLdouble r[] = { 6.0, 3.0, 2.0, 2.0, 2.0, 2.0};
    GLint i;
    glColor3f(0.0,0.0,1.0);
    for (i=0;i<6;i++){
        glutWireSphere(r[i]*0.1, 10.0, 10.0);
        glTranslatef(valx[i]*0.1,0.0,valz[i]*0.1);
    }   

}

void reshape(int width, int height){ 

    int menor = (width < height) ? width : height;

    glViewport(0, 0, menor, menor);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();   
    gluPerspective(60.0, 1.0, 1.0, 128.0); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camaraX, camaraY, camaraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {
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
            printf("i - Show toroide\n");
            printf("t - Show turtle drawing with glBegin()\n");
            printf("e - Show turtle drawing with glutWireSphere()\n");
            printf("q/escape - Quit\n\n");
            break;
        case 'c':
            if (glIsEnabled(GL_CULL_FACE)){     
                glDisable(GL_CULL_FACE);
            }
            else{
                glEnable(GL_CULL_FACE);
            }
            break;
        case '1':
            glRotatef(1.0,1.,0.,0.);
            break;
        case '2':
            glRotatef(1.0,0.,1.,0.);
            break;
        case '3':
            glRotatef(1.0,0.,0.,1.);
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
        case 't':
            mostrarTortuga = true;
            toroide = false;
            tortugaEsferica = false;
            break;
        case 'e':
            tortugaEsferica = true;         
            toroide = false;
            mostrarTortuga = false;
            break;  
        case 'i':
            toroide = true;
            tortugaEsferica = false;            
            mostrarTortuga = false;
            break;  
        case 'q':
        case 27:
            exit(0);
            break;

    }

    glutPostRedisplay();

}

void display(void) {

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


    if(mostarEjes){

        //Función que dibuja los ejes X,Y y Z
        dibujarEjes();  

    }
    
    if(mostrarTortuga){

        //Función que dibuja la tortuga con glBegin()
        drawTurtle();

    }
    
    if(tortugaEsferica){

        //Función que dibuja la tortuga con glutWireSphere()
        drawSphereTurtle();

    }   

    if(toroide){    

        glColor3f(1.0,0.0,0.0);
        glutWireTorus(0.25,0.75, 28, 28); 
        glColor3f(0.0,0.0,1.0) ;
        glutWireCube(.60) ;

        //Primitivas:

        glBegin(GL_TRIANGLES);
            glColor3f(0.0,0.0,1.0);
            glVertex2f(0.0,-0.3);
            glColor3f(0.0,0.0,1.0);
            glVertex2f(-0.3,0.3);
            glColor3f(0.0,0.0,1.0);
            glVertex2f(0.3,0.3);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(1.0,0.0,0.0);
            glVertex3f(0.0,0.3,0.0);
            glColor3f(1.0,0.0,0.0);
            glVertex3f(-0.15,0.0,0.0);
            glColor3f(1.0,0.0,0.0);
            glVertex3f(0.15,0.0,0.0);
        glEnd();


        //Contorno punteado del cuadrado
        glBegin(GL_POINTS);
            //Lado de Abajo
            glVertex2f(-0.33,-0.33);
            glVertex2f(-0.31,-0.33);
            glVertex2f(-0.29,-0.33);
            glVertex2f(-0.27,-0.33);
            glVertex2f(-0.25,-0.33);
            glVertex2f(-0.23,-0.33);
            glVertex2f(-0.21,-0.33);
            glVertex2f(-0.19,-0.33);
            glVertex2f(-0.17,-0.33);
            glVertex2f(-0.15,-0.33);
            glVertex2f(-0.13,-0.33);
            glVertex2f(-0.11,-0.33);
            glVertex2f(-0.09,-0.33);
            glVertex2f(-0.07,-0.33);
            glVertex2f(-0.05,-0.33);
            glVertex2f(-0.03,-0.33);
            glVertex2f(-0.01,-0.33);
            glVertex2f(0.31,-0.33);
            glVertex2f(0.29,-0.33);
            glVertex2f(0.27,-0.33);
            glVertex2f(0.25,-0.33);
            glVertex2f(0.23,-0.33);
            glVertex2f(0.21,-0.33);
            glVertex2f(0.19,-0.33);
            glVertex2f(0.17,-0.33);
            glVertex2f(0.15,-0.33);
            glVertex2f(0.13,-0.33);
            glVertex2f(0.11,-0.33);
            glVertex2f(0.09,-0.33);
            glVertex2f(0.07,-0.33);
            glVertex2f(0.05,-0.33);
            glVertex2f(0.03,-0.33);
            glVertex2f(0.01,-0.33);

            //Lado de Arriba
            glVertex2f(0.33,0.33);
            glVertex2f(-0.31,0.33);
            glVertex2f(-0.29,0.33);
            glVertex2f(-0.27,0.33);
            glVertex2f(-0.25,0.33);
            glVertex2f(-0.23,0.33);
            glVertex2f(-0.21,0.33);
            glVertex2f(-0.19,0.33);
            glVertex2f(-0.17,0.33);
            glVertex2f(-0.15,0.33);
            glVertex2f(-0.13,0.33);
            glVertex2f(-0.11,0.33);
            glVertex2f(-0.09,0.33);
            glVertex2f(-0.07,0.33);
            glVertex2f(-0.05,0.33);
            glVertex2f(-0.03,0.33);
            glVertex2f(-0.01,0.33);
            glVertex2f(0.31,0.33);
            glVertex2f(0.29,0.33);
            glVertex2f(0.27,0.33);
            glVertex2f(0.25,0.33);
            glVertex2f(0.23,0.33);
            glVertex2f(0.21,0.33);
            glVertex2f(0.19,0.33);
            glVertex2f(0.17,0.33);
            glVertex2f(0.15,0.33);
            glVertex2f(0.13,0.33);
            glVertex2f(0.11,0.33);
            glVertex2f(0.09,0.33);
            glVertex2f(0.07,0.33);
            glVertex2f(0.05,0.33);
            glVertex2f(0.03,0.33);
            glVertex2f(0.01,0.33);

            //Lado Izquierdo
            glVertex2f(0.33,-0.33);
            glVertex2f(0.33,-0.31);
            glVertex2f(0.33,-0.29);
            glVertex2f(0.33,-0.27);
            glVertex2f(0.33,-0.25);
            glVertex2f(0.33,-0.23);
            glVertex2f(0.33,-0.21);
            glVertex2f(0.33,-0.19);
            glVertex2f(0.33,-0.17);
            glVertex2f(0.33,-0.15);
            glVertex2f(0.33,-0.13);
            glVertex2f(0.33,-0.11);
            glVertex2f(0.33,-0.09);
            glVertex2f(0.33,-0.07);
            glVertex2f(0.33,-0.05);
            glVertex2f(0.33,-0.03);
            glVertex2f(0.33,-0.01);
            glVertex2f(0.33,0.31);
            glVertex2f(0.33,0.29);
            glVertex2f(0.33,0.27);
            glVertex2f(0.33,0.25);
            glVertex2f(0.33,0.23);
            glVertex2f(0.33,0.21);
            glVertex2f(0.33,0.19);
            glVertex2f(0.33,0.17);
            glVertex2f(0.33,0.15);
            glVertex2f(0.33,0.13);
            glVertex2f(0.33,0.11);
            glVertex2f(0.33,0.09);
            glVertex2f(0.33,0.07);
            glVertex2f(0.33,0.05);
            glVertex2f(0.33,0.03);
            glVertex2f(0.33,0.01);

            //Lado Derecho
            glVertex2f(-0.33,0.33);
            glVertex2f(-0.33,-0.31);
            glVertex2f(-0.33,-0.29);
            glVertex2f(-0.33,-0.27);
            glVertex2f(-0.33,-0.25);
            glVertex2f(-0.33,-0.23);
            glVertex2f(-0.33,-0.21);
            glVertex2f(-0.33,-0.19);
            glVertex2f(-0.33,-0.17);
            glVertex2f(-0.33,-0.15);
            glVertex2f(-0.33,-0.13);
            glVertex2f(-0.33,-0.11);
            glVertex2f(-0.33,-0.09);
            glVertex2f(-0.33,-0.07);
            glVertex2f(-0.33,-0.05);
            glVertex2f(-0.33,-0.03);
            glVertex2f(-0.33,-0.01);
            glVertex2f(-0.33,0.31);
            glVertex2f(-0.33,0.29);
            glVertex2f(-0.33,0.27);
            glVertex2f(-0.33,0.25);
            glVertex2f(-0.33,0.23);
            glVertex2f(-0.33,0.21);
            glVertex2f(-0.33,0.19);
            glVertex2f(-0.33,0.17);
            glVertex2f(-0.33,0.15);
            glVertex2f(-0.33,0.13);
            glVertex2f(-0.33,0.11);
            glVertex2f(-0.33,0.09);
            glVertex2f(-0.33,0.07);
            glVertex2f(-0.33,0.05);
            glVertex2f(-0.33,0.03);
            glVertex2f(-0.33,0.01);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(-0.15,0.3);
            glVertex2f(-0.22,0.15);
            glVertex2f(-0.15,0.3);
            glVertex2f(-0.08,0.15);
            glVertex2f(-0.22,0.15);
            glVertex2f(-0.08,0.15);
        glEnd();

        glBegin(GL_LINE_LOOP);
            glVertex2f(0.15,0.3);
            glVertex2f(0.22,0.15);
            glVertex2f(0.08,0.15);
        glEnd();

        glBegin(GL_LINE_STRIP);
            glVertex2f(-0.315,0.315);
            glVertex2f(-0.315,-0.315);
            glVertex2f(0.315,-0.315);
            glVertex2f(0.315,0.315);
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);
            glVertex2f(0.0,0.0);
            glVertex2f(-0.08,-0.15);
            glVertex2f(0.08,-0.15);     
        glEnd();

    }
    
    glutSwapBuffers();  
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE); 
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Practica 1"); 
    glutDisplayFunc(display);   
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;

}