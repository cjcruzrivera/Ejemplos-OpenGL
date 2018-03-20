#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>

bool command = false; /* command mode */
char strCommand[256];

void drawSphereTurtle() {

    int slices = 40;
    int stacks = 40;

    glPushMatrix();
    glScalef(1.0f, .3f, 1.0f);
    glutSolidSphere(1.0, slices, stacks);
    glPopMatrix();

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

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    drawSphereTurtle();
    glPopMatrix();
    
    glutSwapBuffers();
}

void parseCommand(char* strCommandParse) {
    char *strToken0;
    char *strToken1;
    double val;
    strToken0 = strtok(strCommandParse, " ");
    while ((strToken1 = strtok(NULL, " ")) != NULL) {
        val = atof(strToken1);
        if (!strcmp("fd", strToken0)) { // FORWARD
            glTranslatef(0.0, 0.0, val);
        } else if (!strcmp("bk", strToken0)) { // BACK
            glTranslatef(0.0, 0.0, -val);
        } else if (!strcmp("rt", strToken0)) { // RIGHT
            glRotatef(-val, 0., 1., 0.);
        } else if (!strcmp("lt", strToken0)) { // LEFT
            glRotatef(val, 0., 1., 0.);
        } else if (!strcmp("up", strToken0)) { // UP
            glRotatef(val, 1., 0., 0.);
        } else if (!strcmp("dn", strToken0)) { // DOWN
            glRotatef(-val, 1., 0., 0.);
        }
        strToken0 = strtok(NULL, " ");
        display();
    }
    // EXIT COMMAND MODE
    if (strToken0 != NULL && strncmp(strToken0, "exit", 4) == 0) {
        command = false;
        // HOME
    } else if (strToken0 != NULL && !strcmp("home", strToken0)) {
        glLoadIdentity();
    }
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
    if (command) {
        if (key == 13) {
            strcat(strCommand, " ");
            if (strlen(strCommand) == 1) command = false;
            parseCommand(strCommand);
            strcpy(strCommand, "");
        } else {
            char strKey[2] = " ";
            strKey[0] = key;
            printf(strKey);
            strcat(strCommand, strKey);
        }
    } else { // not in command mode
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
                glRotatef(1.0, 1., 0., 0.);
                break;
            case '2':
                glRotatef(1.0, 0., 1., 0.);
                break;
            case 'i':
                command = true;
                break;
            case 'q':
                exit(0);
                break;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("tortuga");

    //glEnable(GL_COLOR_MATERIAL);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}