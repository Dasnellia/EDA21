#include <iostream>
#include <cstring>
#include "persona.h"


Persona::Persona(const char *d = "", const char *n = "", const char *a = "", int id = 0)
{
    strncpy(DNI, d, 8);
    DNI[8] = '\0';
    strncpy(Nombre, n, 29);
    Nombre[29] = '\0';
    strncpy(Apellidos, a, 29);
    Apellidos[29] = '\0';
    ;

    idEventohash = id;
    evento = nullptr; 
}

const char* Persona::getDNI() const { return DNI; }
const char* Persona::getNombre() const { return Nombre; }
const char* Persona::getApellidos() const { return Apellidos; }
int Persona::getIdEventohash() const { return idEventohash; }
int* Persona::getEvento() const { return evento; }

void Persona::setDNI(const char *d)
{
    strncpy(DNI, d, 8);
    DNI[8] = '\0';
}

void Persona::setNombre(const char *n)
{
    strncpy(Nombre, n, 29);
    Nombre[29] = '\0';
}

void Persona::setApellidos(const char *a)
{
    strncpy(Apellidos, a, 29);
    Apellidos[29] = '\0';
}

void Persona::setIdEventohash(int id)
{
    idEventohash = id;
}

void Persona::setEvento(int *e)
{
    evento = e;
}

bool Persona::igualA(const Persona &otra) const
{
    return (strcmp(DNI, otra.DNI) == 0 &&
            strcmp(Nombre, otra.Nombre) == 0 &&
            strcmp(Apellidos, otra.Apellidos) == 0 &&
            idEventohash == otra.idEventohash);
}
