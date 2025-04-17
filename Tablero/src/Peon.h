#pragma once
#include<iostream>
#include"ETSIDI.h"
#include"Casilla.h"

using namespace ETSIDI;
using namespace std;
class Peon
{
private:
	char color;
public:
	void dibuja();
	bool ComprobarMov(Casilla(casillas)[8][8], int fil1, int col1, int fil2, int col2);
};

