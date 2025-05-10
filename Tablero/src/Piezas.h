#pragma once
//Hacemos incldue de imagen para poder dibujar las piezas

#include"ETSIDI.h"
#include"Imagen.h"
#include<array>

class Casilla;										//Evitas hacer include y con ello evitas dependencias circulares

using namespace ETSIDI;
using std::abs;
using TABLERO = array<array<Casilla, 8>, 8>;

enum State { INVALIDO, NORMAL, PASANTE };
enum Tipo_pieza { NADA, PEON, TORRE, ALFIL, CABALLO, REINA, REY };

class Piezas
{
protected:
	Tipo_pieza tipo;
	char color;

	//Esto hay que cambiarlo
	float tam = 5.075;					//tamaño estandar
	float tam3 = 5.27075, tam2 = 2.9;	//tamaño del droide
	float tam5 = tam, tam6 = 5.4375;		//Tamaño de vader
	float tam7 = 4.7125, tam8 = tam6;	//Tamaño superdroide
	float tam9 = 5.1475, tam10 = 5.5825;	//Tamaño Doku

public:
	virtual void dibujar(float x, float y) {};		//Funcion para dibujar de la clase base
	virtual State comprobarMov(TABLERO& casillas,	//Funcion de comprobar movimiento de la clase base
		Casilla& cas1, Casilla& cas2) = 0;
	virtual char getColor() = 0;						//Funcion de devolver color de la clase base
	virtual bool getMemoria() = 0;
	virtual Tipo_pieza getTipo() = 0;
};



