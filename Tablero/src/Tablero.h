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
#include <vector>


using namespace ETSIDI;							//Para no tener que poner ETSIDI:: siempre
using TABLERO = array<array<Casilla, 8>, 8>;	//Decimos que TABLERO equivale a el array de arrays (ahorramos escribir mucho)

//Hacemos uso de array de arrays ya que es mejor que hacer una matriz en cuanto a rendimiento y flexibilidad

class Tablero
{
private:
	TABLERO casilla;							//Creamos matriz de casillas
	int f, c;					//Esto es para la casilla seleccionada(se puede cambiar)
	int fil_mouse_over, col_mouse_over;
	float x, y, tam_x, tam_y;					//Esto es para el tamaño y posicion del tablero solamente
	//Sprite fondo{ "imagenes/fondo_esapcio_negro.png", 0, 0, 96, 64 };
	Sprite fondo_tablero_sprite{ "imagenes/Tablero_Fondo_1.png", 0, 0, 96, 64 };
	


	std::vector<Casilla*> casillas_resaltadas; // Para almacenar los movimientos posibles de la pieza seleccionada

public:
	Tablero();									//Creamos un constructor para inicializar todo
	~Tablero();
	//Creamos las funciones de dibujar, mover y de seleccion de casilla(hay que moverla al coordinador)
	void dibuja();
	bool mueve(int fil1, int col1, int fil2, int col2, char turnoActual);
	void seleccion(int f1, int c1);
	void deseleccionar();
	void actualizarMovimientosPosibles(int fil, int col); // Actualizar la lista de casillas resaltadas
	const Casilla& getCasilla(int fil, int col) const { return casilla[fil][col]; }
	char getPiezaColor(int fila, int columna) const;

	
};
