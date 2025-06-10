#include <iostream>
#include <cstring> 
#ifndef ENTRADA_H
#define ENTRADA_H

#include "evento.h"
#include "asistente.h"

class Entrada
{
private:
    int idEntrada;
    Evento *evento;
    Asistente *asistente;

public:

    Entrada(int id, Evento *e, Asistente *a);

    int getIdEntrada() const;
    Evento *getEvento() const;
    Asistente *getAsistente() const;

    void setIdEntrada(int id);
    void setEvento(Evento *e);
    void setAsistente(Asistente *a);

    void mostrarEntrada() const;
};

#endif 