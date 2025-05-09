#pragma once
#include "ETSIDI.h"
#include <string>
#include <sstream> 

using namespace ETSIDI;


class Vineta
{
private:
	Sprite vineta{ "imagenes/vineta.png", -4,3,70,75 };
	Sprite fondo{ "imagenes/fondo_esapcio_negro.png", 0, 0, 96, 64 };
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
};

