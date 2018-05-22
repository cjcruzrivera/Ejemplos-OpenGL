/* 
 * Archivo:   main.cpp
 * Camilo José Cruz Rivera 1428907
 * SEGUNDO PARCIAL PARTE PRACTICA
 * Animación de una escena
 * Computación Gráfica
 * 
 * 3 de Abril de 2018
 */

#include <GL/glut.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <math.h>

using namespace std;
GLuint loadBMP_custom(const char * imagepath);
GLuint Texture;
double angle = 0;
double angle2 = 0;
double angle3 = 0;
typedef struct
{
    int X;
    int Y;
    int Z;
    double U;
    double V;
}VERTICES;

const double PI = 3.1415926535897;
const int space = 10;
const int VertexCount = (90 / space) * (360 / space) * 4;
VERTICES VERTEX[VertexCount];


GLfloat anguloCuboX = 0.0f;
GLfloat x = -2.5;
GLfloat y = 0.0;
GLfloat z = -10;

bool der = true;
bool ini = true;
bool pause = false;

float velocidad = 0;
float angulo = 0;
float t = 0;

void DisplaySphere (double R, GLuint texture)
{

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int b;
    glScalef (0.0125 * R, 0.0125 * R, 0.0125 * R);
    //glRotatef (90, 1, 0, 0);
    glBindTexture (GL_TEXTURE_2D, texture);
    glBegin (GL_TRIANGLE_STRIP);
    for ( b = 0; b <VertexCount; b++)
    {
        glTexCoord2f (VERTEX[b].U, VERTEX[b].V);
        glVertex3f (VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);
    }



    for ( b = 0; b <VertexCount; b++)
    {

        glTexCoord2f (VERTEX[b].U, -VERTEX[b].V);

        glVertex3f (VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);

    }
    
    glEnd();
}



void display(void) {
    glClearDepth(1);
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(x,y,z);
    glRotatef(angle3,1,0,0);
    glRotatef(angle,0,1,0);
    glRotatef(angle2,0,0,1);
    DisplaySphere(1, Texture);
    glutSwapBuffers();
}

static void Timer(int n){ 
    if(!pause){
        x = -2.5+velocidad*cos(angulo)*t;
        y = -(0.098/2)*t*t + velocidad*sin(angulo)*t;
        t = t + 0.1;
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


void CreateSphere (double R, double H, double K, double Z) {
    int n;
    double a;
    double b;
    n = 0;
    for( b = 0; b <= 90 - space; b+=space){

        for( a = 0; a <= 360 - space; a+=space)
        {
            VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
            VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
            VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
            VERTEX[n].V = (2 * b) / 360;
            VERTEX[n].U = (a) / 360;

            n++;
            VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
            VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
            VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
            VERTEX[n].V = (2 * (b + space)) / 360;
            VERTEX[n].U = (a) / 360;
            n++;
            VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI) - H;
            VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI) + K;
            VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
            VERTEX[n].V = (2 * b) / 360;
            VERTEX[n].U = (a + space) / 360;
            n++;
            VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) /180 * PI) - H;
            VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) /180 * PI) + K;
            VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
            VERTEX[n].V = (2 * (b + space)) / 360;
            VERTEX[n].U = (a + space) / 360;
            n++;
        }

    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
            case 'h':
                printf("help\n\n");
                printf("c - Toggle culling\n");
                printf("q/escape - Quit\n\n");
                break;
            case 'z':
                angle2++;
                break;
            case 'y':
                angle++;
                break;
            case 'x':
                angle3++;
                break;
            case 'p':
                if(pause){
                    pause  = false;
                }else{
                    pause = true;
                };
                break;
            case 'q':
            case 27:
                exit(0);
                break;
        }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    velocidad = atof(argv[1]);
    angulo = PI*atof(argv[2])/180;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Segundo Parcial Camilo José Cruz Rivera 1428907");
    Texture = loadBMP_custom("textura.bmp");
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_TEXTURE_2D );
    glDepthFunc(GL_LEQUAL);
    CreateSphere(35,0,0,0);
    
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glClearColor(1,1,1,1);
    glutDisplayFunc(display);
	 
    // 100 milliseconds
	Timer(100);
    glutMainLoop();
    
    return 0;
}

GLuint loadBMP_custom(const char * imagepath) {

    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos; // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize; // = width*height*3
    // Actual RGB data
    unsigned char * data;

    // Open the file
    FILE * file = fopen(imagepath, "rb");
    if (!file) {
        printf("Image could not be opened\n");
        return 0;
    }

    if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return false;
    }

    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a correct BMP file\n");
        return 0;
    }

    // Read ints from the byte array
    dataPos = *(int*) &(header[0x0A]);
    imageSize = *(int*) &(header[0x22]);
    width = *(int*) &(header[0x12]);
    height = *(int*) &(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0) imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0) dataPos = 54; // The BMP header is done that way

    // Create a buffer
    data = new unsigned char [imageSize];

    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
}