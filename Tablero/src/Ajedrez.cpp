#pragma once
#include "Tablero.h"
#include "freeglut.h"
#include<iostream>
#include "Coordinador.h"
#include "ETSIDI.h"

Coordinador coordinador;
int fil1, fil2, col1, col2, fil3, col3;
bool flag = false;

//los callback, funciones que seran llamadas automaticamente por la glut
//cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void onSpecialKeyboardDown(int key, int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void reshape(int w, int h);


int main(int argc,char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	
	glutInitWindowSize(1920, 1080);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");
	glutFullScreen();

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);	
	glMatrixMode(GL_PROJECTION);
	gluPerspective( 30.0, 800/600.0f, 0.1, 150);

	coordinador.musica();
	coordinador.actualizarEscalaVentana(1920, 1080);
	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25,OnTimer,0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);
	glutSpecialFunc(onSpecialKeyboardDown); //gestion de los cursores
	glutReshapeFunc(reshape);

	//mundo.inicializa();
	glutPassiveMotionFunc(mouseMotion);
	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();	

	return 0;   
}

void OnDraw(void)
{
	//Borrado de la pantalla	
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

	gluLookAt(0, 0, 120, // posicion del ojo
		0, 0, 0, // hacia que punto mira (0,0,0)
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)*/
	
	//tab.dibuja();
	coordinador.dibuja();
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}

void mouseMotion(int x, int y)
{
	coordinador.MovRaton(x, y);
}

void OnMouseClick(int button, int state, int x, int y) 
{

	coordinador.calcular_Casilla(button, state, x, y);
	coordinador.mouse(button, state, x, y);

	glutPostRedisplay();
	
}

void OnKeyboardDown(unsigned char key, int x, int y)
{
	//poner aqui el c�digo de teclado
	coordinador.teclado(key,x,y);

	glutPostRedisplay();
}

void OnTimer(int value)
{
//poner aqui el c�digo de animacion
	coordinador.animaciones();
	//no borrar estas lineas
	glutTimerFunc(25,OnTimer,0);
	glutPostRedisplay();
}

void onSpecialKeyboardDown(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		coordinador.subirVolumen();
		break;
	case GLUT_KEY_DOWN:
		coordinador.bajarVolumen();
		break;
	default:
		break;
	}
	glutPostRedisplay();
	
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	coordinador.actualizarEscalaVentana(w, h);
}