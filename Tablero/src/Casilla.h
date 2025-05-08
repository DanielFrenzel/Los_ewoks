#pragma once
//Hacemos include de las piezas, asi como de la imagen y ETSIDI

#include "Piezas.h"								
#include"ETSIDI.h"
#include"Imagen.h"

using namespace ETSIDI;

class Casilla
{
private:
	Piezas* pieza;								//Creamos un objeto Piezas	

	int fila;									//fila del tablero
	int columna;								//columna del tablero

public:
	Casilla();									//Constructor
	~Casilla()									//Destructor
	{
		if (pieza!=nullptr) {
			delete pieza;						
			pieza = nullptr;
		}
	}
	
	void dibuja();								//Funcion de dibujar piezas
	void Casilla_seleccionada();				//Funcion para dibujar casilla seleccionada

												//Getters
	char getcolor();
	int &getfila();
	int &getcolumna();
	Piezas* getficha();

												//Setters
	void setficha(Piezas* p);
	void setPosicion(int fil, int col);
};

