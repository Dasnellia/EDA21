#include <iostream>
#include <cstring>
#ifndef ASISTENTE_H
#define ASISTENTE_H
#include "persona.h"


class Asistente : public Persona {
private:
    bool Asistencia;
    int prioridad;
    int idasistente;
    char tipoAsistente[20]; // "VIP", "Normal", etc.

public:
    // Constructor
    Asistente(const char* d = "", const char* n = "", const char* a = "", int id = 0, const char* tipo = "");

    void RegistrarAsistencia();
    
    bool getAsistencia() const;
    int getPrioridad() const;
    int getId() const;
    const char* getTipoAsistente() const;
    void setAsistencia(bool asistencia);
    void setPrioridad(int p);
    void setId(int id);
    void setTipoAsistente(const char* tipo);
    void mostrarAsistente() const;
};

#endif