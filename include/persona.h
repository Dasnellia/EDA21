#include <iostream>
#include <cstring> 
#include "evento.h"

#ifndef PERSONA_H
#define PERSONA_H

class Persona
{
private:
    char DNI[9];
    char Nombre[30];
    char Apellidos[30];
    int idEventohash;
    int *evento;

public:

    Persona(const char *d = "", const char *n = "", const char *a = "", int id = 0);
   
    const char *getDNI() const;
    const char *getNombre() const;
    const char *getApellidos() const;
    int getIdEventohash() const;
    int *getEvento() const;


    void setDNI(const char *d);

    void setNombre(const char *n);

    void setApellidos(const char *a);

    void setIdEventohash(int id);

    const char *getNombreCompleto() const;
    void setNombreCompleto(const char *n, const char *a);

    void setEvento(int *e);
    void mostrarPersona() const;

    bool igualA(const Persona &otra) const;
};

#endif // PERSONA_H