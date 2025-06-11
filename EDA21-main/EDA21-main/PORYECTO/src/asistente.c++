#include <iostream>
#include <cstring> 
#include "asistente.h"

Asistente::Asistente(const char *d = "", const char *n = "", const char *a = "", int id = 0, const char *tipo = "")
    : Persona(d, n, a, id), Asistencia(false), prioridad(1)
{

    if (strcmp(tipo, "VIP") == 0)
    {
        prioridad = 5;
    }
}

void Asistente::RegistrarAsistencia()
{
    Asistencia = true;
}

// Getters
bool Asistente::getAsistencia() const { return Asistencia; }
int Asistente::getPrioridad() const { return prioridad; }
