#pragma once
#include"Casilla.h"
#include "MovPiezas.h"

class Movimiento
{
private:
    MovPiezas pieza;
public:
    //void movimiento(Casilla &cas, Casilla &cas2);
    void movimiento(Casilla** cas, int fil1, int col1, int fil2, int col2);
};

