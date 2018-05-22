//en este ejemplo se utiliza el buffer de profundidad para mostrar que
//realmente el triangulo rojo que esta dezplazado
//10 unidades atras del verde.
#include <GL/glut.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//

//Definición del modelo de una luz
GLfloat light_Ambient[4] = {0.4, 0.4, 0.4, 1.0};
GLfloat light_Diffuse[4] = {0.7, 0.7, 0.7, 1.0};
GLfloat light_Position[4] = {20.0, 15.0, 10.0, 1.0};

//Definición de las caracteristicas opticas de reflexión
GLfloat material[4] = {1.0, 0.2, 0.2, 1.0};
GLfloat RedMaterial[4] = {1.0, 0.0, 0.0, 1.0};
GLfloat GreenMaterial[4] = {0.0, 1.0, 0.0, 1.0};
GLfloat BlueMaterial[4] = {0.0, 0.0, 1.0, 1.0};
GLfloat WhiteMaterial[4] = {1.0, 1.0, 1.0, 1.0};
/* los valores de los materiales se van a sumar para tener una
totalidad, que antes se multiplico a la luz
ambiente+difuso + especular*/
//Cuadric
GLUquadricObj *quadobj;
void luces(void)
{
	//Cargando las ecuaciones de luz
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ambient);
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_Position);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 1.0);
}
void EjesReferencia()
{
	glBegin(GL_LINES);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RedMaterial);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(20.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GreenMaterial);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 20.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WhiteMaterial);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 20.0);
	glEnd();
}
void cilindro()
{
	quadobj = gluNewQuadric();
	gluQuadricDrawStyle(quadobj, GLU_FILL); //drawStyle
											//GLU FILL,
											//GLU LINE,
											//GLU POINT,
											//GLU SILHOUETTE
	gluQuadricNormals(quadobj, GLU_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(quadobj,
				2,				//GLdouble
				2,				//GLdouble
				3,				//GLdouble
				15,				//GLint
				15);
	glPopMatrix();
	//**************************************************
	//Para el ejercicio 2 retire los comentarios "/**/"
	//Se dibujará un segundo cilindro
	//**************************************************

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(-7.0, 0.0, -27.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(quadobj,
				2,
				2,
				3,
				15,
				15);
	glPopMatrix();

	gluDeleteQuadric(quadobj);
}
void RenderScene(void)
{
	/*Borra frame buffer*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*Prepara la luz*/
	luces();
	/*Prepara ejes de referencia*/
	EjesReferencia();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	/*Prepara un cilindro*/
	cilindro();
	/*Render de las primitivas*/
	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); //NOTE QUE SE ASIGNO GLUT_DEPTH utilizar buffer de profundidad
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("utilizando camara con OpenGL");
	glutDisplayFunc(RenderScene);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	//
	//Habilitando el bufer de produndidad
	glEnable(GL_DEPTH_TEST);
	//cte GL_DEPTH_TEST HABILITADO
	//
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-5,5,-5,5,-10,10); esta es proyeccion plana
	gluPerspective(15, 800 / 600, .1, 1000); //explicacion abajo
	//fov:angulo de apertura de la camara=>35 grados
	//relacion de aspecto 3:4,16:9=>800/600
	//plano de vista cercano. mayor de 0 => .1
	//plano de vista lejano. =>1000.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(25, 10, 35,
			  4, 2, -5, // si pones 5,5,-5 se ve cortado
			  0, 1, 0);
	//camara tiene un ojo, posicion de lente y giro de tripie.No esta en pixeles
	// eyex, eyey, eyez: especifica la poisicon de la lente de la camara u ojo.
	// centerx, centery, centerz: especifica la posion del punto al que se mira
	//upx, upy, upz: especfica el vector de orientacion de la camara
	//
	glTranslatef(4, 3, -0.5);
	glutMainLoop();
	return 0;
}