#pragma once
#include "ETSIDI.h"
#include"Imagen.h"
#include <string>
#include <sstream> 

using namespace ETSIDI;


class Vineta
{
private:
	float xf=-4, yf=3, xv=0, yv=0;
	float tamf_x=96, tamf_y=64, tamv_x=70, tamv_y=75;
	//Sprite vineta{ "imagenes/vineta.png", xv,yv,tamv_x,tamv_y };
	//Sprite fondo{ "imagenes/fondo_esapcio_negro.png",xf,yf,tamf_x,tamf_y };
	Sprite tablero{ "imagenes/Tablero_Futurista.png", 0, 0, 56, 56 };
	std::string textoCompleto;
	std::string textoMostrado;
	size_t indiceTexto = 0;
	float tiempoAcumulado = 0.0f;
	float velocidadTexto = 0.05f;  // segundos entre letras (~20 letras por segundo)
	bool textoTerminado = false;
	int end = 0;
public:
	void dibujar();
	void mostrarTextoAnimado(const std::string& texto, float deltaTiempo, float posX, float posY);

	friend class Imagen;
};

