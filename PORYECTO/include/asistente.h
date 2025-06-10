#include <iostream>
#include <cstring>
#ifndef ASISTENTE_H
#define ASISTENTE_H
#include "entrada.h"


class Asistente : public Persona {
private:
    bool Asistencia;
    int prioridad;

public:
    // Constructor
    Asistente(const char* d = "", const char* n = "", const char* a = "", int id = 0, const char* tipo = "");

    void RegistrarAsistencia();
    // Getters
    bool getAsistencia() const;
    int getPrioridad() const;
};

#endif