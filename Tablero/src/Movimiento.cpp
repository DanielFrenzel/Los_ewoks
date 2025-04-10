#include "Movimiento.h"

void Movimiento::movimiento(Casilla &cas, Casilla &cas2)
{
	int fich = cas.getficha();
	if (fich != 0)
	{
		cas2.setficha(fich, cas.getcolor());
	}
	cas.setficha(0,0);
}