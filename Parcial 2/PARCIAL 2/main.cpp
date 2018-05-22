/* 
 
Universidad del Valle
Sede Meléndez

Fecha: 23/05/2017

Nombre: Juan Pablo Moreno Muñoz
Código: 1423437

Asignatura:  Computación Gráfica
Profesor: John Alexander Vargas

*/


#include <GL/glut.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <math.h>

// Nuevo: CAMERA
#include "Camara.h"

// Nuevo: LUZ
#include "Light.h"
#include "primitivas.h"

using namespace std;

GLuint loadBMP_custom(const char * imagepath);
GLuint Texture;
GLuint texturaPielTortuga;
GLuint texturaCaparazon;

// Nuevo: CAMARA
static Camara *objetoCamara = new Camara(0.0f, 1.0f, -3.0f);
static int old_x, old_y;

// Nuevo: LUZ & MATERIAL
static Light *LOCAL_MyLights[3];
static int current_mode = 0;
static int current_light = -1;

// Nuevo: LUZ & MATERIAL
GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {2.0f, 5.0f, 5.0f, 0.0f};

const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};


// Nuevo: CAMARA

void MouseMotion(int x, int y) {
    old_y = y;
    old_x = x;
}

// Nuevo: CAMARA

void Examinar(int x, int y) {
    float rot_x, rot_y;
    rot_y = (float) (old_y - y);
    rot_x = (float) (x - old_x);
    objetoCamara->Rotar_Latitud(rot_y * DEGREE_TO_RAD);
    objetoCamara->Rotar_Longitud(rot_x * DEGREE_TO_RAD);
    old_y = y;
    old_x = x;
    glutPostRedisplay();
}

// Nuevo: LUZ & MATERIAL

void Mouse_Spot_Abrir_Cerrar(int x, int y) {

    float step;

    step = (float) (y - old_y);
    old_y = y;

    if (LOCAL_MyLights[current_light]->spotCutOff + step < 90 && LOCAL_MyLights[current_light]->spotCutOff + step > 0)
        LOCAL_MyLights[current_light]->spotCutOff += step;

    LOCAL_MyLights[current_light]->needsUpdate = TRUE;
    glutPostRedisplay();
}

// Nuevo: LUZ & MATERIAL

void Mouse_Spot(int x, int y) {
    float rot_x, rot_y;

    rot_y = (float) (old_y - y);
    rot_x = (float) (x - old_x);

    LOCAL_MyLights[current_light]->Rotar_Spot_Latitud(rot_y * DEGREE_TO_RAD);
    LOCAL_MyLights[current_light]->Rotar_Spot_Longitud(rot_x * DEGREE_TO_RAD);

    old_y = y;
    old_x = x;

    glutPostRedisplay();
}


// Nuevo: LUZ & MATERIAL

void Mouse_Luces(int x, int y) {
    float rot_x, rot_y;
    rot_y = (float) (old_y - y);
    rot_x = (float) (x - old_x);
    LOCAL_MyLights[current_light]->Rotar_Luces_Latitud(rot_y * DEGREE_TO_RAD);
    LOCAL_MyLights[current_light]->Rotar_Luces_Longitud(rot_x * DEGREE_TO_RAD);

    LOCAL_MyLights[current_light]->pointAtInfinity[0] = LOCAL_MyLights[current_light]->position[0];

    LOCAL_MyLights[current_light]->pointAtInfinity[1] = LOCAL_MyLights[current_light]->position[1];

    LOCAL_MyLights[current_light]->pointAtInfinity[2] = LOCAL_MyLights[current_light]->position[2];

    old_y = y;
    old_x = x;
    glutPostRedisplay();
}

void moverCamaraArriba(double arriba){
    objetoCamara->camAtZ = objetoCamara->camAtZ + (-arriba * DEGREE_TO_RAD); 
}

void moverCamaraAbajo(double abajo){
    objetoCamara->camAtZ = objetoCamara->camAtZ + (abajo * DEGREE_TO_RAD);  
}

void moverCamaraDerecha(double derecha){
    objetoCamara->camAtX= objetoCamara->camAtX + (derecha * DEGREE_TO_RAD);    
}

void moverCamaraIzquierda(double izquierda){
    objetoCamara->camAtX= objetoCamara->camAtX + (-izquierda * DEGREE_TO_RAD);    
}

static void SpecialKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1:
            glutPassiveMotionFunc(MouseMotion);
            objetoCamara->camMovimiento = CAM_STOP;
            break;
        case GLUT_KEY_F2:
            glutPassiveMotionFunc(Examinar);
            objetoCamara->camMovimiento = CAM_EXAMINAR;
            break;
        case GLUT_KEY_F3:
            glutPassiveMotionFunc(MouseMotion);
            objetoCamara->camMovimiento = CAM_PASEAR;
            objetoCamara->camAtY = 0;
            objetoCamara->camViewY = 0;
            objetoCamara->SetDependentParametersCamera();
            break;

            // Nuevo: LUZ
        case GLUT_KEY_F8:
            if (current_mode != 0 && current_mode != 7) break;
            current_mode = 7;
            if (current_light == -1) glutPassiveMotionFunc(Mouse_Luces);
            if (current_light != 2) current_light++;
            else current_light = 0;
            printf("Luz actual = %d\n", current_light);
            break;
            
        // Nuevo: LUZ & MATERIAL
        case GLUT_KEY_F9:
            if (current_light != -1)
                if (LOCAL_MyLights[current_light]->switched)
                    LOCAL_MyLights[current_light]->SwitchLight(FALSE);
                else LOCAL_MyLights[current_light]->SwitchLight(TRUE);
            break;

        case GLUT_KEY_PAGE_UP:
            //AvanceFreeCamera( objetoCamara, 0.5f );
            if (objetoCamara->camAperture < 175 * DEGREE_TO_RAD)
                objetoCamara->camAperture = objetoCamara->camAperture + 2.5f * DEGREE_TO_RAD;
            break;

        case GLUT_KEY_PAGE_DOWN:
            //AvanceFreeCamera( objetoCamara, -0.5f );
            if (objetoCamara->camAperture > 5 * DEGREE_TO_RAD)
                objetoCamara->camAperture = objetoCamara->camAperture - 2.5f * DEGREE_TO_RAD;
            break;

        case GLUT_KEY_UP:
            //objetoCamara->Rotar_Latitud(2.5f * DEGREE_TO_RAD);
            //PitchCamera( objetoCamara, 3.0f * DEGREE_TO_RAD );
            moverCamaraArriba(0.9);
            break;            

        case GLUT_KEY_DOWN:
            //objetoCamara->Rotar_Latitud(-2.5f * DEGREE_TO_RAD);
            //PitchCamera( objetoCamara, -3.0f * DEGREE_TO_RAD );
            moverCamaraAbajo(0.9);
            break;

        case GLUT_KEY_LEFT:
            //objetoCamara->Rotar_Longitud(-2.5f * DEGREE_TO_RAD);
            //YawCamera( objetoCamara, 3.0f * DEGREE_TO_RAD );
            moverCamaraIzquierda(0.9);
            break;

        case GLUT_KEY_RIGHT:
            //objetoCamara->Rotar_Longitud(2.5f * DEGREE_TO_RAD);
            //YawCamera( objetoCamara, -3.0f * DEGREE_TO_RAD );
            moverCamaraDerecha(0.9);
            break;

        case GLUT_KEY_HOME: //Reset Camera
            objetoCamara->camAtX = 0;
            objetoCamara->camAtY = 0;
            objetoCamara->camAtZ = 0;
            objetoCamara->camViewX = 0;
            objetoCamara->camViewY = 1;
            objetoCamara->camViewZ = -3;
            objetoCamara->SetDependentParametersCamera();
            break;
        default:
            printf("key %d %c X %d Y %d\n", key, key, x, y);
    }
    glutPostRedisplay();
}

void Zoom(int x, int y) {
    float zoom;
    zoom = (float) ((y - old_y) * DEGREE_TO_RAD);
    old_y = y;
    switch (objetoCamara->camMovimiento) {
        case CAM_EXAMINAR:
            if (objetoCamara->camAperture + zoom > (5 * DEGREE_TO_RAD) &&
                    objetoCamara->camAperture + zoom < 175 * DEGREE_TO_RAD)
                objetoCamara->camAperture = objetoCamara->camAperture + zoom;
            break;
    }
    glutPostRedisplay();
}

void Andar(int x, int y) {
    float rotacion_x, avance_y;
    avance_y = (float) (y - old_y) / 10;
    rotacion_x = (float) (old_x - x) * DEGREE_TO_RAD / 5;
    objetoCamara->YawCamera(rotacion_x);
    objetoCamara->AvanceFreeCamera(avance_y);
    old_y = y;
    old_x = x;
    glutPostRedisplay();
}


// Nuevo: LUZ & MATERIAL

void Mouse_Luces_Acercar_Alejar(int x, int y) {
    float step;
    step = (float) (y - old_y) / 20.0f;
    old_y = y;
    LOCAL_MyLights[current_light]->Acercar_Alejar_Luces(step);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    old_x = x;
    old_y = y;
    switch (button) {
        case GLUT_LEFT_BUTTON:
            // Nuevo: LUZ
            if (current_light > 0) {
                if (state == GLUT_DOWN)
                    glutMotionFunc(Mouse_Luces_Acercar_Alejar);
                if (state == GLUT_UP) {
                    glutPassiveMotionFunc(Mouse_Luces);
                    glutMotionFunc(NULL);
                }
            } else {
                switch (objetoCamara->camMovimiento) {
                    case CAM_EXAMINAR:
                        if (state == GLUT_DOWN) glutMotionFunc(Zoom);
                        if (state == GLUT_UP) {
                            glutPassiveMotionFunc(Examinar);
                            glutMotionFunc(NULL);
                        }
                        break;
                    case CAM_PASEAR:
                        if (state == GLUT_DOWN) glutMotionFunc(Andar);
                        if (state == GLUT_UP) glutMotionFunc(NULL);
                        break;
                }
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


// Nuevo: LUZ & MATERIAL

void AumentarLuz(int pos) {

    light_ambient[pos] += 0.1f;
    light_diffuse[pos] += 0.1f;
    light_specular[pos] += 0.1f;

    int luz = LOCAL_MyLights[current_light]->id;

    glLightfv(luz, GL_AMBIENT, light_ambient);
    glLightfv(luz, GL_DIFFUSE, light_diffuse);
    glLightfv(luz, GL_SPECULAR, light_specular);
    glLightfv(luz, GL_POSITION, light_position);

}

// Nuevo: LUZ & MATERIAL

void DisminuirLuz(int pos) {

    light_ambient[pos] -= 0.1f;
    light_diffuse[pos] -= 0.1f;
    light_specular[pos] -= 0.1f;

    int luz = LOCAL_MyLights[current_light]->id;

    glLightfv(luz, GL_AMBIENT, light_ambient);
    glLightfv(luz, GL_DIFFUSE, light_diffuse);
    glLightfv(luz, GL_SPECULAR, light_specular);
    glLightfv(luz, GL_POSITION, light_position);

}

void drawSphereTurtle() {

    int slices = 40;
    int stacks = 40;
    glColor3f(1.0,1.0,1.0);
    
    texturaCaparazon = loadBMP_custom("tortuguita.bmp");
    
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glScalef(1.0f, .3f, 1.0f);
    glutSolidSphere(1.0, slices, stacks);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    texturaPielTortuga = loadBMP_custom("piel.bmp");
    glEnable(GL_TEXTURE_2D);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    
    
    glPushMatrix();
    glTranslatef(.7f, 0.0f, .7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.7f, 0.0f, .7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.7f, 0.0f, -.7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.7f, 0.0f, -.7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0f, .6f, 1.0f);
    glTranslatef(0.0f, 0.0f, -1.2f);
    glutSolidSphere(.4, slices, stacks);
    glPopMatrix();
}

void esfera() {

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glutSolidSphere(1, 80, 80);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void dibujarEjes() {

    //Dibuja los ejes

    //Eje x
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(20.0, 0.0, 0.0);
    glEnd();
    //Eje y
    glColor3f(0.0, 0.7, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 20.0, 0.0);
    glEnd();

    //Eje z
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 20.0);
    glEnd();

}

void display() {

    float At[3]; // Nuevo: LUZ
    float Direction[3]; // Nuevo: LUZ
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // Nuevo: LUZ
    glEnable(GL_LIGHTING); // Nuevo: LUZ

    // Nuevo: LUZ & MATERIAL
    LOCAL_MyLights[0]->SetLight();
    LOCAL_MyLights[1]->SetLight();
    LOCAL_MyLights[2]->SetLight();
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    glPushMatrix();
    dibujarEjes();
    //esfera();
    drawSphereTurtle();

    // Nuevo: LUZ
    switch (current_light) {
        case 0:
            At[0] = LOCAL_MyLights[current_light]->position[0];
            At[1] = LOCAL_MyLights[current_light]->position[1];
            At[2] = LOCAL_MyLights[current_light]->position[2];
            Direction[0] = -LOCAL_MyLights[current_light]->position[0];
            Direction[1] = -LOCAL_MyLights[current_light]->position[1];
            Direction[2] = -LOCAL_MyLights[current_light]->position[2];
            Draw_Parallel(At);
            Draw_Meridian(At);
            Draw_Vector(At, Direction);
            break;
        case 1:
            At[0] = LOCAL_MyLights[current_light]->position[0];
            At[1] = LOCAL_MyLights[current_light]->position[1];
            At[2] = LOCAL_MyLights[current_light]->position[2];
            Direction[0] = -LOCAL_MyLights[current_light]->position[0];
            Direction[1] = -LOCAL_MyLights[current_light]->position[1];
            Direction[2] = -LOCAL_MyLights[current_light]->position[2];
            Draw_Parallel(At);
            Draw_Meridian(At);
            Draw_Vector(At, Direction);
            break;
        case 2:
            At[0] = LOCAL_MyLights[current_light]->position[0];
            At[1] = LOCAL_MyLights[current_light]->position[1];
            At[2] = LOCAL_MyLights[current_light]->position[2];
            Direction[0] = -LOCAL_MyLights[current_light]->position[0];
            Direction[1] = -LOCAL_MyLights[current_light]->position[1];
            Direction[2] = -LOCAL_MyLights[current_light]->position[2];
            Draw_Parallel(At);
            Draw_Meridian(At);
            Draw_Vector(At, Direction);
            break;
        default:
            break;
    }

    glPopMatrix();

    // Nuevo: CAMERA
    objetoCamara->SetGLCamera();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    /*
    GLsizei dim;

    if (width < height) {
        dim = width;
    } else {
        dim = height;
    }
     */

    glViewport(0, 0, width, height);

    // Nuevo: CAMERA
    objetoCamara->SetGLAspectRatioCamera();

    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); */

}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {
        case 'h':
            printf("help\n\n");
            printf("c - Toggle culling\n");
            printf("q/escape - Quit\n\n");
            break;

        case 'c':
            if (glIsEnabled(GL_CULL_FACE))
                glDisable(GL_CULL_FACE);
            else
                glEnable(GL_CULL_FACE);
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
        case 'r':
            DisminuirLuz(0);
            break;
        case 'R':
            AumentarLuz(0);
            break;
        case 'g':
            DisminuirLuz(1);
            break;
        case 'G':
            AumentarLuz(1);
            break;
        case 'b':
            DisminuirLuz(2);
            break;
        case 'B':
            AumentarLuz(2);
            break;
        case 'q':
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();

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

int main(int argc, char** argv) {

    glutInit(&argc, argv);


    // Nuevo: LUZ
    int i;

    //Creamos las luces y damos a cada una sus características
    for (i = 0; i < 3; i++) {
        LOCAL_MyLights[i] = new Light();
        LOCAL_MyLights[i]->type = AGA_DIRECTIONAL;
        LOCAL_MyLights[i]->id = GL_LIGHT0 + i;
        LOCAL_MyLights[i]->position[0] = 1.0f;
        LOCAL_MyLights[i]->position[1] = 1.0f;
        LOCAL_MyLights[i]->position[2] = 1.0f;
        LOCAL_MyLights[i]->position[3] = 0.0f;
        LOCAL_MyLights[i]->pointAtInfinity[0] = LOCAL_MyLights[0]->position[0];
        LOCAL_MyLights[i]->pointAtInfinity[1] = LOCAL_MyLights[0]->position[1];
        LOCAL_MyLights[i]->pointAtInfinity[2] = LOCAL_MyLights[0]->position[2];
    }



    //glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Practica Tortuga");

    // Nuevo: LUZ
    glEnable(GL_COLOR_MATERIAL);

    glutDisplayFunc(display);


    // Nuevo: CAMERA
    glutPassiveMotionFunc(MouseMotion);
    glutSpecialFunc(SpecialKey);
    glutMouseFunc(mouse);

    //Texture = loadBMP_custom("tortuguita.bmp");

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

