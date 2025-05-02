#pragma once
#include "Tablero.h"
#include"Casilla.h"
#include "Peon.h"
#include "Rey.h"
#include "Torre.h"
#include "Caballo.h"
#include "Alfil.h"

class Coordinador
{
private:
	Sprite Estrella{ "imagenes/inicio/ESTRELLA.png", 0, 0, 20, 25 };
	Sprite MenuInicial{ "imagenes/inicio/MENU4.png", 0, 0, 96, 64 };
	Sprite BotonDuelo{ "imagenes/inicio/BOTON_DUELO.png", 0, 0, 15, 15 };
	Sprite BotonDuelo2{ "imagenes/inicio/BOTON_DUELO2.png", 0, 0, 15, 15 };
	Sprite BotonIA{ "imagenes/inicio/BOTON_IA.png", 0, 0, 15, 15 };
	Sprite BotonIA2{ "imagenes/inicio/BOTON_IA2.png", 0, 0, 15, 15 };
	Sprite BotonAJUSTES{ "imagenes/inicio/BOTON_AJUSTES.png", 0, 0, 15, 15 };
	Sprite BotonAJUSTES2{ "imagenes/inicio/BOTON_AJUSTES2.png", 0, 0, 15, 15 };

	Sprite BotonSalida{ "imagenes/inicio/Boton_salida.png", 0, 0, 20, 20 };
	Sprite BotonSalida2{ "imagenes/inicio/Boton_salida2.png", 0, 0, 20, 20 };

	Sprite BotonSonido{ "imagenes/inicio/BOTON_ALTAVOZ.png", 0, 0, 5, 5 };
	Sprite BotonSonido2{ "imagenes/inicio/BOTON_ALTAVOZ2.png", 0, 0, 5, 5 };
private:
	Tablero* tablero = nullptr;
	int ficha;
	Peon peon;
	Rey rey;
	Torre torre;
	Caballo caballo;
	Alfil alfil;
	bool turno = 0;
	bool resaltar_duelo = 0;
	bool resaltar_ia = 0;
	bool resaltar_ajustes = 0;
	bool resaltar_salida = 0;
	bool resaltar_altavoz = 0;
	float bote = 0.0f;
	float angulo_bote = 0.0f;
	bool subiendo_bote = 1;
		
public:
	void setTablero(Tablero* t);
	void MovRaton(int x, int y);
	void movimiento(int fil1, int col1, int fil2, int col2);
	bool compMov(int fil1, int col1, int fil2, int col2);
	Coordinador();
	void dibuja();
	void boteEstrella();

protected:
	enum Estado { INICIO, DUELO, IA, AJUSTES, SONIDO, MUSICA, AYUDA, CREDITOS, NORMAS, MOVIMIENTOS };
	Estado estado;


};

