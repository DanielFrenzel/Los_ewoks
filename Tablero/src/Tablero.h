#pragma once
#include"ETSIDI.h"
#include "Casilla.h"
#include<vector>
#include<iostream>
#include"Movimiento.h"
#include"Imagen.h"

using namespace ETSIDI;


class Tablero
{
private:
	Sprite tablero{ "imagenes/tablero.png",0,0,64,64 };
	Casilla** casilla;  //lo creamos como memoria dinamica para poder pasrlo por punteros a las piezas y optimizar el juego
	int patron1[8]= { 1, 2, 3, 5, 4, 3, 2, 1 };
	int patron2[8] = { 6, 6, 6, 6, 6, 6, 6, 6 };
	Movimiento mover;
	int f=0, c=0;
	Imagen im;
	float _x = 0, _y = 0, tamx = 64, tamy = 64;

public:
	Tablero();
	void dibuja();
	void mueve(int fil1, int col1, int fil2, int col2);
	void seleccion(int f1, int c1);
	friend class Movimiento;
	friend class Imagen;

};

