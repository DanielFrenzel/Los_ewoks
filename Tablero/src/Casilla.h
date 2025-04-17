#pragma once
#include "Piezas.h"
#include"ETSIDI.h"
#include<iostream>


using namespace ETSIDI;


class Casilla
{
private:
	Piezas piezas;
	Sprite casilla_seleccionada{ "imagenes/casilla_seleccionada.png",0,0,8,8 };
	int fila;//fila del tablero
	int columna;//columna del tablero


public:
	Casilla();
	Casilla(int &f, int &c,int fich, char col);
	void dibuja();
	int getficha();
	void setficha(int f, char col);
	char getcolor();
	int getfila();
	int getcolumna();
	void Casilla_seleccionada();

};

