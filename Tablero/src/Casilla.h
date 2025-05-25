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
	bool esta_resaltada;
	bool esta_resaltada_mouse_over;
	float tam = 4.0;

public:
	Casilla(); //Constructor
	~Casilla()									//Destructor
	{
		if (pieza != nullptr) {
			delete pieza;
			pieza = nullptr;
		}
	}

	void dibuja();								//Funcion de dibujar piezas
	void setResaltada(bool resaltada) { esta_resaltada = resaltada; }
	bool getResaltada() const { return esta_resaltada; } 

	//Getters
	char getcolor();
	int& getfila();
	int& getcolumna();
	Piezas* getficha() const;
	bool getMemoria();
	Tipo_pieza getTipo();
	bool getResaltadaMouseOver() const { return esta_resaltada_mouse_over; }

	//Setters
	void setficha(Piezas* p);
	void setPosicion(int fil, int col);
	void setResaltadaMouseOver(bool resaltada) { esta_resaltada_mouse_over = resaltada; }
};

