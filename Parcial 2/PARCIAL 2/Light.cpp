/**
 * Práctica Computación Gráfica
 * Luz
 * Fecha de entrega: 02/05/2017
 * Universidad del Valle
 * EISC
 *
 * Integrantes: 
 *
 * Jhonier Andrés Calero Rodas		1424599
 * Juan Pablo Moreno Muñoz		1423437
 * Joan Manuel Tovar Guzmán		1423124
 * 
 */

#include <GL/glut.h>
#include "Vector_tools.h"
#include "Light.h"
#include <iostream>

using namespace std;

Light::Light() {
    SetDefaultLight();
}

Light::Light(const Light& orig) {
}

Light::~Light() {
}

void Light::distanciaLuz(double x, double y, double z) {
    
    double val_x = pow(x, 2);
    double val_y = pow(y, 2);
    double val_z = pow(z, 2);
    
    double raiz = sqrt(val_x + val_y + val_z);
    
    this->position[3] = raiz;
    
    this->a = raiz;
    this->b = raiz;
    this->c = raiz;
}

void Light::SetDefaultLight() {
    int ierr = 0;
    float intensity;
    float vx, vy, vz;
    // directional light
    this->type = AGA_DIRECTIONAL;
    this->id = -1;
    this->switched = FALSE;
    this->white = TRUE;
    this->attenuation = TRUE;
    this->needsUpdate = TRUE;
    intensity = 0.0f;
    this->ambient[0] = intensity;
    this->ambient[1] = intensity;
    this->ambient[2] = intensity;
    this->ambient[3] = 1.0f;
    intensity = 0.8f;
    this->diffuse[0] = intensity;
    this->diffuse[1] = intensity;
    this->diffuse[2] = intensity;
    this->diffuse[3] = 1.0f;
    intensity = 0.0f;
    this->specular[0] = intensity;
    this->specular[1] = intensity;
    this->specular[2] = intensity;
    this->specular[3] = 1.0f;
    this->position[0] = 1.0f;
    this->position[1] = 1.0f;
    this->position[2] = 1.0f;
    this->position[3] = 1.0f;
    vx = 1.0f;
    vy = 1.0f;
    vz = 1.0f;
    VectorNormalize(&ierr, &vx, &vy, &vz);
    this->pointAtInfinity[0] = vx;
    this->pointAtInfinity[1] = vy;
    this->pointAtInfinity[2] = vz; // The light is "placed" at point "V" in the infinite
    this->pointAtInfinity[3] = 0.0f; // So light rays flow in the direction of vector "-v"
    vx = -1.0f;
    vy = -1.0f;
    vz = -1.0f;
    VectorNormalize(&ierr, &vx, &vy, &vz);
    this->spotDirection[0] = vx;
    this->spotDirection[1] = vy;
    this->spotDirection[2] = vz;
    this->spotDirection[3] = 0.0f;
    this->spotExponent = 10.0f;
    this->spotCutOff = 30.0f; // must be degrees
    this->a = 0.0f; // GL_QUADRATIC_ATTENUATION
    this->b = 0.0f; // GL_LINEAR_ATTENUATION
    this->c = 1.0f; // GL_CONSTANT_ATTENUATION
}

void Light::SwitchLight(int status) {
    if (!this) return;
    if (this->id < GL_LIGHT0) return;
    this->switched = status;
    if (status) {
        glEnable(this->id);
        this->needsUpdate = TRUE;
    } else {
        glDisable(this->id);
    }
}

void Light::SetLight() {
    int lightId;
    if (!this) return;
    if (!this->switched) return;
    if (this->id < GL_LIGHT0) return;
    lightId = this->id;

    // Geometric parameters will be always set when the scene is redrawn
    if (this->type == AGA_DIRECTIONAL) {
        glLightfv(lightId, GL_POSITION, this->pointAtInfinity);
        glLightfv(lightId, GL_POSITION, this->position);
    } else if (this->type == AGA_POSITIONAL) {
        glLightfv(lightId, GL_POSITION, this->position);
    } else {
        glLightfv(lightId, GL_POSITION, this->position);
        glLightfv(lightId, GL_SPOT_DIRECTION, this->spotDirection);
    }

    distanciaLuz(this->position[0], this->position[0], this->position[0]);
    
    glLightf(lightId, GL_CONSTANT_ATTENUATION, this->c);
    glLightf(lightId, GL_LINEAR_ATTENUATION, this->b);
    glLightf(lightId, GL_QUADRATIC_ATTENUATION, this->a);

    // These other parameters are seldom changed
    // So, they will be set only when any one of them is changed. The user interface
    // must set "needsUpdate" to TRUE, whenever any of these parameters changes
    if (this->needsUpdate) {
        this->needsUpdate = FALSE;
        glLightfv(lightId, GL_AMBIENT, this->ambient);
        glLightfv(lightId, GL_DIFFUSE, this->diffuse);
        glLightfv(lightId, GL_SPECULAR, this->specular);
        if (this->type == AGA_SPOT) {
            glLightf(lightId, GL_SPOT_EXPONENT, this->spotExponent);
            glLightf(lightId, GL_SPOT_CUTOFF, this->spotCutOff);
        } else {
            glLighti(lightId, GL_SPOT_EXPONENT, 0);
            glLighti(lightId, GL_SPOT_CUTOFF, 180);
        }
        
        if (this->attenuation || this->type == AGA_DIRECTIONAL) {
            glLighti(lightId, GL_CONSTANT_ATTENUATION, 1);
            glLighti(lightId, GL_LINEAR_ATTENUATION, 0);
            glLighti(lightId, GL_QUADRATIC_ATTENUATION, 0);
        } else {
            glLightf(lightId, GL_CONSTANT_ATTENUATION, this->c);
            glLightf(lightId, GL_LINEAR_ATTENUATION, this->b);
            glLightf(lightId, GL_QUADRATIC_ATTENUATION, this->a);
        }
         
    }
}

void Light::Rotar_Luces_Longitud(float inc) {
    float vIn[3];
    vIn[0] = this->position[0];
    vIn[1] = this->position[1];
    vIn[2] = this->position[2];
    VectorRotY(vIn, inc);
    this->position[0] = vIn[0];
    this->position[2] = vIn[2];
}

void Light::Rotar_Luces_Latitud(float inc) {
    float vIn[3];
    vIn[0] = this->position[0];
    vIn[1] = this->position[1];
    vIn[2] = this->position[2];
    VectorRotXZ(vIn, inc, TRUE);
    this->position[0] = vIn[0];
    this->position[1] = vIn[1];
    this->position[2] = vIn[2];
}

void Light::Acercar_Alejar_Luces(float step) {
    int ierr;
    float vaX, vaY, vaZ;
    float modulo;
    vaX = this->position[0];
    vaY = this->position[1];
    vaZ = this->position[2];
    VectorNormalize(&ierr, &vaX, &vaY, &vaZ);
    vaX = step * vaX;
    vaY = step * vaY;
    vaZ = step * vaZ;
    // Set new position
    modulo = sqrt(pow(this->position[0] + vaX, 2) + pow(this->position[1] + vaY, 2) +
            pow(this->position[2] + vaZ, 2));
    if (modulo < 0.8f) return;
    this->position[0] += vaX;
    this->position[1] += vaY;
    this->position[2] += vaZ;

    //    this->diffuse[0] = 1 / modulo;
    //    this->diffuse[1] = 1 / modulo;
    //    this->diffuse[2] = 1/ modulo;
    //    this->diffuse[3] = 1.0f;
}

void Light::Rotar_Spot_Latitud(float inc) {
    float vIn[3];
    vIn[0] = this->spotDirection[0];
    vIn[1] = this->spotDirection[1];
    vIn[2] = this->spotDirection[2];
    VectorRotXZ(vIn, inc, TRUE);
    this->spotDirection[0] = vIn[0];
    this->spotDirection[1] = vIn[1];
    this->spotDirection[2] = vIn[2];
}

void Light::Rotar_Spot_Longitud(float inc) {
    float vIn[3];
    vIn[0] = this->spotDirection[0];
    vIn[1] = this->spotDirection[1];
    vIn[2] = this->spotDirection[2];
    VectorRotY(vIn, inc);
    this->spotDirection[0] = vIn[0];
    this->spotDirection[2] = vIn[2];
}



