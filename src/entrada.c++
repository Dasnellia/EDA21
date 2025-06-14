#include <iostream>
#include <cstring>
#include "entrada.h"


Entrada::Entrada(int id, Evento *e = nullptr, Asistente *a = nullptr)
    : idEntrada(id), evento(e), asistente(a) {}

int Entrada::getIdEntrada() const { return idEntrada; }
Evento Entrada::*getEvento() const { return evento; }
Asistente Entrada::*getAsistente() const { return asistente; }

void Entrada::setIdEntrada(int id) { idEntrada = id; }
void Entrada::setEvento(Evento *e) { evento = e; }
void Entrada::setAsistente(Asistente *a) { asistente = a; }

void Entrada::mostrarEntrada() const
{
    std::cout << "ID Entrada: " << idEntrada << std::endl;
    if (evento)
    {
        evento->mostrarEvento();
    }
    else
    {
        std::cout << "No hay evento asignado." << std::endl;
    }
    if (asistente)
    {
        std::cout << "Hay un asistente asignado." << std::endl;
    }
    else
    {
        std::cout << "No hay asistente asignado." << std::endl;
    }
}
