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
	//General--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Sprite Estrella{ "imagenes/inicio/ESTRELLA.png", 0, 0, 20, 25 };
	Sprite MenuInicial{ "imagenes/inicio/MENU4.png", 0, 0, 96, 64 };

	Sprite BotonSalida{ "imagenes/inicio/Boton_salida.png", 0, 0, 20, 20 };
	Sprite BotonSalida2{ "imagenes/inicio/Boton_salida2.png", 0, 0, 20, 20 };

	Sprite BotonSonido{ "imagenes/inicio/BOTON_ALTAVOZ.png", 0, 0, 5, 5 };
	Sprite BotonSonido1_5{ "imagenes/inicio/BOTON_ALTAVOZ1.5.png", 0, 0, 5, 5 };
	Sprite BotonSonido2{ "imagenes/inicio/BOTON_ALTAVOZ2.png", 0, 0, 5, 5 };
	Sprite BotonSonido2_5{ "imagenes/inicio/BOTON_ALTAVOZ2.5.png", 0, 0, 5, 5 };

	Sprite BotonAtras{ "imagenes/inicio/BOTON_ATRAS.png", 0, 0, 4, 4 };
	Sprite BotonAtras2{ "imagenes/inicio/BOTON_ATRAS2.png", 0, 0, 4, 4 };

	Sprite BotonInterrogacion{ "imagenes/inicio/BOTON_INTERROGACION.png", 0, 0, 20, 20 };
	Sprite BotonInterrogacion2{ "imagenes/inicio/BOTON_INTERROGACION2.png", 0, 0, 20, 20 };

	//Primera Pantalla menu---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Sprite BotonDuelo{ "imagenes/inicio/BOTON_DUELO.png", 0, 0, 15, 15 };
	Sprite BotonDuelo2{ "imagenes/inicio/BOTON_DUELO2.png", 0, 0, 15, 15 };
	Sprite BotonIA{ "imagenes/inicio/BOTON_IA.png", 0, 0, 15, 15 };
	Sprite BotonIA2{ "imagenes/inicio/BOTON_IA2.png", 0, 0, 15, 15 };
	Sprite BotonAJUSTES{ "imagenes/inicio/BOTON_AJUSTES.png", 0, 0, 15, 15 };
	Sprite BotonAJUSTES2{ "imagenes/inicio/BOTON_AJUSTES2.png", 0, 0, 15, 15 };

	//Pantalla AJUSTES---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Sprite BotonSonidoGeneral{ "imagenes/inicio/BOTON_SONIDO.png", 0, 0, 15, 15 };
	Sprite BotonSonidoGeneral2{ "imagenes/inicio/BOTON_SONIDO2.png", 0, 0, 15, 15 };
	Sprite BotonMusica{ "imagenes/inicio/BOTON_MUSICA.png", 0, 0, 15, 15 };
	Sprite BotonMusica2{ "imagenes/inicio/BOTON_MUSICA2.png", 0, 0, 15, 15 };
	Sprite BotonAyuda{ "imagenes/inicio/BOTON_AYUDA.png", 0, 0, 15, 15 };
	Sprite BotonAyuda2{ "imagenes/inicio/BOTON_AYUDA2.png", 0, 0, 15, 15 };
	Sprite BotonCreditos{ "imagenes/inicio/BOTON_CREDITOS.png", 0, 0, 15, 15 };
	Sprite BotonCreditos2{ "imagenes/inicio/BOTON_CREDITOS2.png", 0, 0, 15, 15 };

	//Pantalla AYUDA---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Sprite BotonNormas{ "imagenes/inicio/BOTON_NORMAS.png", 0, 0, 15, 15 };
	Sprite BotonNormas2{ "imagenes/inicio/BOTON_NORMAS2.png", 0, 0, 15, 15 };
	Sprite BotonMovimientos{ "imagenes/inicio/BOTON_MOVIMIENTOS.png", 0, 0, 15, 15 };
	Sprite BotonMovimientos2{ "imagenes/inicio/BOTON_MOVIMIENTOS2.png", 0, 0, 15, 15 };

protected:
	enum Estado { INICIO, DUELO, IA, AJUSTES, SONIDO, MUSICA, AYUDA, CREDITOS, NORMAS, MOVIMIENTOS };

private:
	Estado estado;
	Estado estado_anterior;

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
	bool resaltar_sonido = 0;
	bool resaltar_musica = 0;
	bool resaltar_ayuda = 0;
	bool resaltar_creditos = 0;
	bool resaltar_normas = 0;
	bool resaltar_movimientos = 0;
	bool resaltar_atras = 0;
	bool resaltar_interrogacion = 0;
	bool pulsado_sonido = 0; //Servira para cambiar el icono de sonido
	float bote = 0.0f;
	float angulo_bote = 0.0f;
	bool subiendo_bote = 1;
	
public:
	void setTablero(Tablero* t);
	void MovRaton(int x, int y);
	void mouse(int button, int state, int x, int y);
	void movimiento(int fil1, int col1, int fil2, int col2);
	bool compMov(int fil1, int col1, int fil2, int col2);
	Coordinador();
	void dibuja();
	void boteEstrella();
	void musica();

	//Getters
	Estado getEstado() const;
	Estado getEstadoAnterior() const;

	//Setters
	void setEstado(Estado nuevo_estado);
	void setEstadoAnterior(Estado nuevo_estado_anterior);


};

