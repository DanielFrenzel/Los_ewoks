#pragma once
#include <iostream>
#include"ETSIDI.h"
#include"Imagen.h"


using namespace std;
using namespace ETSIDI;


class Piezas
{
private:
	int fila;
	int columna;
	float _x;//Lugar en x del tablero
	float _y;//Lugar en y del tablero
	int ficha;// 1->Torre  2->Caballo  3->Alfil  4->Rey  5->Reina  6->Peon
	char color;

	Imagen imagen;
	float tam = 7;
	float tam3 = 7.27, tam2 = 4;//tama�o del droide
	float tam5 = 7, tam6 = 7.5;//Tama�o de vader
	float tam7 = 6.5, tam8 = 7.5;//Tama�o superdroide
	float tam9 = 7.1, tam10 = 7.7;//Tama�o Doku

	/*//Sprites de piezas blancas
	Sprite peonB{ "imagenes/WhitePawn.png",0,0,5,5 };
	Sprite caballoB{ "imagenes/WhiteKnight.png",0,0,5,5 };
	Sprite alfilB{ "imagenes/WhiteBishop.png",0,0,5,5 };
	Sprite torreB{ "imagenes/WhiteRook.png",0,0,5,5 };
	Sprite reyB{ "imagenes/WhiteKing.png",0,0,5,5 };
	Sprite reinaB{ "imagenes/WhiteQueen.png",0,0,5,5 };

	//Sprites de piezas negras
	Sprite peonN{ "imagenes/BlackPawn.png",0,0,5,5 };
	Sprite caballoN{ "imagenes/BlackKnight.png",0,0,5,5 };
	Sprite alfilN{ "imagenes/BlackBishop.png",0,0,5,5 };
	Sprite torreN{ "imagenes/BlackRook.png",0,0,5,5 };
	Sprite reyN{ "imagenes/BlackKing.png",0,0,5,5 };
	Sprite reinaN{ "imagenes/BlackQueen.png",0,0,5,5 };*/

public:
	void lugar(int f, int c);
	void dibujar();
	void setficha(int f);
	void setcolor(char col);
	char getcolor();
	int getficha();
	int getfila();
	int getcolumna();

	friend class Imagen;

};


