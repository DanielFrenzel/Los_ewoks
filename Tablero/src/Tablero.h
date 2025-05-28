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
#include <string>

using namespace ETSIDI;							//Para no tener que poner ETSIDI:: siempre
using TABLERO = array<array<Casilla, 8>, 8>;	//Decimos que TABLERO equivale a el array de arrays (ahorramos escribir mucho)

//Hacemos uso de array de arrays ya que es mejor que hacer una matriz en cuanto a rendimiento y flexibilidad

class Tablero
{
private:
	TABLERO casilla;							//Creamos matriz de casillas
	int f, c, bioma = 0;					//Esto es para la casilla seleccionada(se puede cambiar)
	int fil_mouse_over = -1; // Almacena la última casilla con mouse over
	int col_mouse_over = -1;
	float x, y, tam_x, tam_y;					//Esto es para el tamaño y posicion del tablero solamente
	//Sprite fondo{ "imagenes/fondo_esapcio_negro.png", 0, 0, 96, 64 };

	std::string rutasFondo[4] = {
  "imagenes/Tablero_Fondo_Hoch.png",
  "imagenes/Fondo_tablero_Tatooine.png",
  "imagenes/Fondo_tablero_Sorgan.png",
  "imagenes/Tablero_Fondo_Hoch.png",
	};

	int peon_doble_avance_columna_anterior;
	int peon_doble_avance_fila_anterior;


	std::vector<Casilla*> casillas_resaltadas; // Para almacenar los movimientos posibles de la pieza seleccionada

public:
	Tablero();									//Creamos un constructor para inicializar todo
	~Tablero();
	//Creamos las funciones de dibujar, mover y de seleccion de casilla(hay que moverla al coordinador)
	void dibuja();
	bool mueve(int fil1, int col1, int fil2, int col2, char turnoActual);
	void seleccion(int fil, int col, char turnoActual); 
	void actualizarMovimientosPosibles(int fil, int col, char turnoActual); 
	void deseleccionar();
	const Casilla& getCasilla(int fil, int col) const { return casilla[fil][col]; }
	char getPiezaColor(int fila, int columna) const;
	Casilla& getCasilla(int fil, int col);
	const TABLERO& getTableroConst() const { return casilla; } 
	void resaltarCapturasObligatorias(const std::vector<std::pair<Casilla*, Casilla*>>& capturas_list);
	
	
	void resetPeonDobleAvance();
	void setPeonDobleAvance(int fil, int col);

	int contarPiezas(char color_a_contar) const; 

	void setMouseOver(int fil, int col);
	void clearMouseOver();
	void set_Bioma(int i);
	
};
