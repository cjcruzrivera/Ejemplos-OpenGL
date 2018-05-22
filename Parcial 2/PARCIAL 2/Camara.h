/*
 * Cámara
 * Fecha de entrega: 27/03/2017
 * Profesor: John Alexander Vargas
 *
 * Integrantes:
 *
 * Jhonier Andrés Calero Rodas      1424599
 * Juan Pablo Moreno Muñoz          1423437
 * Joan Manuel Tovar Guzmán         1423124
 *
 * Universidad del Valle
 * Computación Gráfica
 * EISC  
 * 2017-I
 
 */

#ifndef CAMARA_H
#define CAMARA_H

#define CAM_PARALLEL 1
#define CAM_CONIC 2
#define CAM_STOP 0
#define CAM_EXAMINAR 1
#define CAM_PASEAR 2

#include <GL/glut.h>
#include "Vector_tools.h"

class Camara {
public:
    Camara(float positionX, float positionY, float positionZ);
    Camara(const Camara& orig);
    virtual ~Camara();

    void SetCamera( float viewX, float viewY, float viewZ,
            float atX, float atY, float atZ,
            float upX, float upY, float upZ);
    void SetDependentParametersCamera();
    void SetGLCamera();
    void SetGLAspectRatioCamera();
    // Free camera advances "step" following vector VA, step admits negative values
    void AvanceFreeCamera( float step);
    // ROTATION
    void YawCamera( float angle); // local axis Y camera
    void Rotar_Latitud( float inc);
    void Rotar_Longitud(float inc);




    // we consider a rigth handed reference system for the camera
    // V point where the camera is placed (world coordinates)
    // A point the camera is looking at (world coordinates)
    // up vector : unit vector, perpendicular to AV (world componnents)
    // origin camera reference system : at V
    // Z camera : defined by vector from A to V (penetrates the viewer’s eye)
    // Y camera : defined by up vector
    // X camera : looking from V towards A goes rigthwards
    // View point
    float camViewX; 
    float camViewY;
    float camViewZ;
    // look At point
    float camAtX; 
    float camAtY;
    float camAtZ;
    // Up vector
    float camUpX; 
    float camUpY;
    float camUpZ;
    float camAperture; // field of view radians // NOTE : OpenGL uses degrees
    // defined as they are used by OpenGL
    // always => positive ; Far > Near (distance from plane to camera origin)
    float camNear;
    float camFar;
    int camProjection; // PARALLEL or CONIC
    int camMovimiento; // EXAMINAR, ANDAR, TRIPODE or PAN
    // ****** dependent values ******
    // window system dependent
    float aspectRatio;
    // for ortho projection
    float x1, x2, y1, y2, z1, z2;
    // camera i j k vectors in world coordinates
    float camIX, camIY, camIZ;
    float camJX, camJY, camJZ;
    float camKX, camKY, camKZ;
private:

};

#endif /* CAMARA_H */

