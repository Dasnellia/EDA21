#include <iostream>
#ifndef FRANJAHORARIA_H
#define FRANJAHORARIA_H
#include <ctime>

class FranjaHoraria {
public:
    FranjaHoraria();
    FranjaHoraria(int h, int a, int d, int me);
    FranjaHoraria(int fechacompleta);

    int getHora() const;
    int getAnio() const;
    int getDia() const;
    int getMes() const;

    void setHora(int h);
    void setAnio(int a);
    void setDia(int d);
    void setMes(int me);

    bool igualA(const FranjaHoraria &otra) const;
    bool antesDe(const FranjaHoraria &otra) const;
    int getFechanumerica() const;

private:
    int hora;
    int anio;
    int dia;
    int mes;
    std::tm fechaHora;
};

#endif // FRANJAHORARIA_H