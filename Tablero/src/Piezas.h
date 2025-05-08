#pragma once
//Hacemos incldue de imagen para poder dibujar las piezas

#include"ETSIDI.h"
#include"Imagen.h"
#include<array>

class Casilla;										//Evitas hacer include y con ello evitas dependencias circulares

using namespace ETSIDI;
using std::abs;
using TABLERO = array<array<Casilla, 8>, 8>;

class Piezas
{
protected:
	char color;

	//Esto hay que cambiarlo
	float tam = 7;					//tamaño estandar
	float tam3 = 7.27, tam2 = 4;	//tamaño del droide
	float tam5 = 7, tam6 = 7.5;		//Tamaño de vader
	float tam7 = 6.5, tam8 = 7.5;	//Tamaño superdroide
	float tam9 = 7.1, tam10 = 7.7;	//Tamaño Doku

public:
	virtual void dibujar(float x, float y) {};		//Funcion para dibujar de la clase base
	virtual bool comprobarMov(TABLERO& casillas,	//Funcion de comprobar movimiento de la clase base
		Casilla& cas1, Casilla& cas2)=0;
	virtual char getColor()=0;						//Funcion de devolver color de la clase base

};


