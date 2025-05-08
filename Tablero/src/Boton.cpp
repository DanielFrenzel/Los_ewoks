#include "Boton.h"
#include "ETSIDI.h"
Boton::Boton(
	const std::string& rutaNormal,
	const std::string& rutaResaltado,
	float anchoInicial,
	float altoInicial
	)
	: spriteNormal(rutaNormal.c_str(), 0, 0, anchoInicial, altoInicial),
	spriteResaltado(rutaResaltado.c_str(), 0, 0, anchoInicial, altoInicial),
	x(0), y(0), ancho(anchoInicial), alto(altoInicial)
	, regionX1(0), regionX2(0), regionY1(0), regionY2(0)
{
}
void Boton::setRegion(float x1, float x2, float y1, float y2) 
{
	regionX1 = x1;
	regionX2 = x2;
	regionY1 = y1;
	regionY2 = y2;
	
}
void Boton::setPos(float nuevox, float nuevoy)
{
	x = nuevox;
	y = nuevoy;
	spriteNormal.setPos(x, y);
	spriteResaltado.setPos(x, y);

}
void Boton::setSize(float nuevoAncho, float nuevoAlto)
{
	ancho = nuevoAncho;
	alto = nuevoAlto;
	spriteNormal.setSize(ancho, alto);
	spriteResaltado.setSize(ancho, alto);
}

bool Boton::ratonEncima(int rx, int ry) 
{
	return (rx >= regionX1 && rx <= regionX2 && ry >= regionY1 && ry <= regionY2);
}

void Boton::actualizaResaltado(int rx, int ry)
{
	resaltado = ratonEncima(rx, ry);
	resaltado = (rx >= regionX1 && rx <= regionX2 && ry >= regionY1 && ry <= regionY2);
}

void Boton::draw() 
{
	if (resaltado == 1)
	{
		spriteResaltado.draw();
	}
	else
	{
		spriteNormal.draw();
	}
}