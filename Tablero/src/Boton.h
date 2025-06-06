#pragma once
#include <string>
#include "ETSIDI.h"
using ETSIDI::Sprite;
class Boton
{
private:
	Sprite spriteNormal;
	Sprite spriteResaltado;
	float x, y;
	float ancho, alto;
	bool resaltado = false;
	float regionX1, regionX2, regionY1, regionY2;

public:
	//constructor
	Boton(const std::string& RutaNormal, const std::string& RutaResaltado,
		float anchoInicial, float altoInicial);

	//Setters
	void setPos(float nuevox, float nuevoy);
	void setSize(float nuevoAncho, float nuevoAlto);
	void setRegion(float x1, float x2, float y1, float y2);

	//getters
	float getX() const { return x; }
	float getY() const { return y; }

	//Metodo que commprueba si el raton esta encima o no
	bool ratonEncima(int rx, int ry) ;
	
	//Metodo que actualiza el resaltado
	void actualizaResaltado(int rx, int ry);

	//Para dibujar
	void draw() ;
};

