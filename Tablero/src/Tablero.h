#pragma once
#include"ETSIDI.h"
#include "Casilla.h"
#include<vector>
#include<iostream>
#include"Movimiento.h"

using namespace ETSIDI;


class Tablero
{
private:
	Sprite tablero{ "imagenes/tablero.png",0,0,64,64 };
	Casilla casilla[8][8];
	int patron1[8]= { 1, 2, 3, 5, 4, 3, 2, 1 };
	int patron2[8] = { 6, 6, 6, 6, 6, 6, 6, 6 };
	Movimiento mover;
	int f=0, c=0;

public:
	Tablero();
	void dibuja();
	void mueve(int fil1, int col1, int fil2, int col2);
	void seleccion(int f1, int c1);
	friend class Movimiento;

};

