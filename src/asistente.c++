#include "asistente.h"
#include <iostream>
#include <cstring>
using namespace std;

// Constructor
Asistente::Asistente(const char* d, const char* n, const char* a, int id, const char* tipo)
    : Persona(d, n, a), Asistencia(false), prioridad(1), idasistente(id) {
    strncpy(tipoAsistente, tipo, sizeof(tipoAsistente) - 1);
    tipoAsistente[sizeof(tipoAsistente) - 1] = '\0'; // Seguridad en el string
}

// Marcar asistencia
void Asistente::RegistrarAsistencia() {
    Asistencia = true;
}

// Getters
bool Asistente::getAsistencia() const {
    return Asistencia;
}

int Asistente::getPrioridad() const {
    return prioridad;
}

int Asistente::getId() const {
    return idasistente;
}

const char* Asistente::getTipoAsistente() const {
    return tipoAsistente;
}

// Setters
void Asistente::setAsistencia(bool asistencia) {
    Asistencia = asistencia;
}

void Asistente::setPrioridad(int p) {
    prioridad = p;
}

void Asistente::setId(int id) {
    idasistente = id;
}

void Asistente::setTipoAsistente(const char* tipo) {
    strncpy(tipoAsistente, tipo, sizeof(tipoAsistente) - 1);
    tipoAsistente[sizeof(tipoAsistente) - 1] = '\0';
}

// Mostrar información del asistente
void Asistente::mostrarAsistente() const {
    cout << "ID: " << idasistente << "\n";
    cout << "Tipo: " << tipoAsistente << "\n";
    cout << "Nombre: " << getNombre() << "\n";
    cout << "DNI: " << getDNI() << "\n";
    cout << "Prioridad: " << prioridad << "\n";
    cout << "Asistencia: " << (Asistencia ? "Sí" : "No") << "\n";
}
