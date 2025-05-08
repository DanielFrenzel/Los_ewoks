#pragma once
//Hacemos include de ETISIDI, Casilla, Piezas, Movimiento, las propias piezas y de array (para hacer un array de arrays)
#include"ETSIDI.h"
#include "Casilla.h"
#include"Movimiento.h"
#include"Imagen.h"
#include"Peon.h"
#include"Alfil.h"
#include"Torre.h"
#include"Caballo.h"
#include"Rey.h"
#include"Reina.h"
#include <array>


using namespace ETSIDI;							//Para no tener que poner ETSIDI:: siempre
using TABLERO = array<array<Casilla, 8>, 8>;	//Decimos que TABLERO equivale a el array de arrays (ahorramos escribir mucho)

//Hacemos uso de array de arrays ya que es mejor que hacer una matriz en cuanto a rendimiento y flexibilidad

class Tablero
{
private:
	TABLERO casilla;							//Creamos matriz de casillas
	int f, c;									//Esto es para la casilla seleccionada(se puede cambiar)
	float x, y, tam_x, tam_y;					//Esto es para el tamaño y posicion del tablero solamente

public:
	Tablero();									//Creamos un constructor para inicializar todo

	//Creamos las funciones de dibujar, mover y de seleccion de casilla(hay que moverla al coordinador)
	void dibuja();
	void mueve(int fil1, int col1, int fil2, int col2);
	void seleccion(int f1, int c1);
};

