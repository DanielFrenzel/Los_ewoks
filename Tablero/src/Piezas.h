#pragma once
//Hacemos incldue de imagen para poder dibujar las piezas

#include"ETSIDI.h"
#include"Imagen.h"
#include<array>
#include <vector>

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
	float tam = 4;					//tamaño estandar
	float tam3 = 4.16389, tam2 = 2.291;	//tamaño del droide
	float tam5 = tam, tam6 = 4.29523;		//Tamaño de vader
	float tam7 = 3.7316, tam8 = tam6;	//Tamaño superdroide
	float tam9 = 4.07, tam10 = 4.41;	//Tamaño Doku

public:
	virtual void dibujar(float x, float y) {};		//Funcion para dibujar de la clase base
	virtual State comprobarMov(TABLERO& casillas,	//Funcion de comprobar movimiento de la clase base
		Casilla& cas1, Casilla& cas2) = 0;
	virtual std::vector<Casilla*> movimientosPosibles(const TABLERO& tablero, Casilla& origen) = 0;
	virtual char getColor() = 0;						//Funcion de devolver color de la clase base
	virtual bool getMemoria() = 0;
	virtual Tipo_pieza getTipo() = 0;
};



