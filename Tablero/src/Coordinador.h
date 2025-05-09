#pragma once
#include <string>
#include "Tablero.h"
#include "Casilla.h"
#include "Peon.h"
#include "Rey.h"
#include "Torre.h"
#include "Caballo.h"
#include "Alfil.h"
#include "ETSIDI.h"
#include <vector>
#include "Boton.h"

using namespace ETSIDI;							//Para no tener que poner ETSIDI:: siempre
using TABLERO = array<array<Casilla, 8>, 8>;	//Decimos que TABLERO equivale a el array de arrays (ahorramos escribir mucho)

class Coordinador
{
private:
	//General--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Sprite Estrella{ "imagenes/inicio/ESTRELLA.png", 0, 0, 20, 25 };
	Sprite MenuInicial{ "imagenes/inicio/MENU4.png", 0, 0, 96, 64 };

	Sprite BotonInterrogacion{ "imagenes/inicio/BOTON_INTERROGACION.png", 0, 0, 20, 20 };
	Sprite BotonInterrogacion2{ "imagenes/inicio/BOTON_INTERROGACION2.png", 0, 0, 20, 20 };

	//Creditos---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Sprite Titulo1Creditos{ "imagenes/recursos/T1.png", 0, 0, 15, 15 };
	Sprite Titulo3Creditos{ "imagenes/recursos/T3.png", 0, 0, 15, 15 };
	Sprite ChessWarsCreditos{ "imagenes/recursos/CW3.png", 0, 0, 19, 15 };
	Sprite FondoEstrellas{ "imagenes/recursos/FONDO_ESTRELLAS.png", 0, 0, 96, 64 };

	//Volumen---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Sprite TextoVolumen{ "imagenes/recursos/TextoVolumen.png", 0,0,20,20 };
	Sprite Volumen0{ "imagenes/recursos/Volumen0.png", 0,0,30,25 };
	Sprite Volumen25{ "imagenes/recursos/Volumen25.png", 0,0,15,15 };
	Sprite Volumen50{ "imagenes/recursos/Volumen50.png", 0,0,15,15 };
	Sprite Volumen75{ "imagenes/recursos/Volumen75.png", 0,0,15,15 };
	Sprite Volumen100{ "imagenes/recursos/Volumen100.png", 0,0,15,15 };
	
protected:
	enum Estado { INICIO, DUELO, IA, AJUSTES, SONIDO, MUSICA, AYUDA, CREDITOS, NORMAS, MOVIMIENTOS };

private:
	Estado estado;
	Estado estado_anterior;
	//Botone varios
	Boton botonSalida{ "imagenes/inicio/Boton_salida.png", "imagenes/inicio/Boton_salida2.png", 20, 20 };
	Boton botonAtras{ "imagenes/inicio/BOTON_ATRAS.png", "imagenes/inicio/BOTON_ATRAS2.png", 4, 4 };
	Boton botonAltavozON{ "imagenes/inicio/BOTON_ALTAVOZ.png", "imagenes/inicio/BOTON_ALTAVOZ1.5.png", 5, 5 };
	Boton botonAltavozOFF{ "imagenes/inicio/BOTON_ALTAVOZ2.png", "imagenes/inicio/BOTON_ALTAVOZ2.5.png", 5, 5 };

	//Inicio
	Boton botonDuelo{ "imagenes/inicio/BOTON_DUELO.png", "imagenes/inicio/BOTON_DUELO2.png", 15, 15 };
	Boton botonIA{ "imagenes/inicio/BOTON_IA.png", "imagenes/inicio/BOTON_IA2.png", 15, 15 };
	Boton botonAjustes{ "imagenes/inicio/BOTON_AJUSTES.png", "imagenes/inicio/BOTON_AJUSTES2.png", 15, 15 };
	//Ajustes
	Boton botonSonidoGeneral{ "imagenes/inicio/BOTON_SONIDO.png", "imagenes/inicio/BOTON_SONIDO2.png", 15, 15 };
	Boton botonMusica{ "imagenes/inicio/BOTON_MUSICA.png", "imagenes/inicio/BOTON_MUSICA2.png", 15, 15 };
	Boton botonAyuda{ "imagenes/inicio/BOTON_AYUDA.png", "imagenes/inicio/BOTON_AYUDA2.png", 15, 15 };
	Boton botonCreditos{ "imagenes/inicio/BOTON_CREDITOS.png", "imagenes/inicio/BOTON_CREDITOS2.png", 15, 15 };
	//Ayuda
	Boton botonNormas{ "imagenes/inicio/BOTON_NORMAS.png", "imagenes/inicio/BOTON_NORMAS2.png", 15, 15 };
	Boton botonMovimientos{ "imagenes/inicio/BOTON_MOVIMIENTOS.png", "imagenes/inicio/BOTON_MOVIMIENTOS2.png", 15, 15 };
	//Musica
	Boton botonMusica1{ "imagenes/inicio/cancion1.png", "imagenes/inicio/Cancion1Seleccionada.png", 15, 15 };
	Boton botonMusica2{ "imagenes/inicio/cancion2.png", "imagenes/inicio/Cancion2Seleccionada.png", 15, 15 };
	Boton botonMusica3{ "imagenes/inicio/cancion3.png", "imagenes/inicio/Cancion3Seleccionada.png", 15, 15 };
		
private:
	Tablero tablero;							//Creamos matriz de casillas
	int ficha;
	Peon peon;
	Rey rey;
	Torre torre;
	Caballo caballo;
	Alfil alfil;
	bool turno = 0;
	//bool resaltar_altavoz = 0;
	bool pulsado_sonido = 0; //Servira para cambiar el icono de sonido
	//Variables para las animaciones
	float bote = 0.0f;
	float angulo_bote = 0.0f;
	float anim_CW = 0.0f;
	bool subiendo_bote = 1;
	float flote_titulo = 0.0f;
	float tamx, tamy;
	bool activacion_titulo2 = 0;
	float tiempo_titulo1 = 0.0f;
	bool activacion_titulo1 = 0;
	bool musica_creditos_activada = 0;
	bool activacion_titulo3 = 0;
	float movimiento_titulo3 = 0.0f;
	float tiempoespera_titulo3 = 0.0f;
	//Variable musica
	int musica_actual = -1; // -1: ninguna, 0: menu, 1: creditos
	//Variables para el rescalado (nos ayuda a que el juego funcione en cualqier pantalla)
	int ancho_ventana = 1920;
	int alto_ventana = 1080;
	float escalaX = 1.0f;
	float escalaY = 1.0f;
	//Variables volumen
	int volumen=100;
	Sprite volumenes[5] = {
		Sprite("imagenes/recursos/Volumen0.png",  0,0,30,30),
		Sprite("imagenes/recursos/Volumen25.png", 0,0,30,30),
		Sprite("imagenes/recursos/Volumen50.png", 0,0,30,30),
		Sprite("imagenes/recursos/Volumen75.png", 0,0,30,30),
		Sprite("imagenes/recursos/Volumen100.png",0,0,30,30)
	};
	std::string rutasVolumen[4] = {
		"sonidos/BLASTER25.mp3",
		"sonidos/BLASTER50.mp3",
		"sonidos/BLASTER75.mp3",
		"sonidos/BLASTER100.mp3"
	};
	std::string rutasMenu[4] = {    
	  "sonidos/Musica125.mp3",
	  "sonidos/Musica150.mp3",
	  "sonidos/Musica175.mp3",
	  "sonidos/Musica1100.mp3",
	};

	vector <Estado> memoria_Estado;
	
public:
	Coordinador();
	void MovRaton(int x, int y);
	void mouse(int button, int state, int x, int y);
	void mueve(int fil1, int col1, int fil2, int col2); //movimiento del tablero pasado a través del coordinador
	void seleccion(int f1, int c1);				//pasar la casilla seleccionada al tablero
	void dibuja();								//dibujar el juego
	void animaciones();
	void musica();

	//Getters
	Estado getEstado() const;
	Estado getEstadoAnterior() const;

	//Setters
	void setEstado(Estado nuevo_estado);
	void setEstadoAnterior(Estado nuevo_estado_anterior);

	//Control de volumen
	void subirVolumen();
	void bajarVolumen();

	//Funcions para el escalado de las coordenadas(nos permite que funcione en pantalla completa en cualquier pantalla)
	void actualizarEscalaVentana(int ancho_actual, int alto_actual);
	float escalarX(float x) const;
	float escalarY(float y) const;
};

