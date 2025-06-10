#include <iostream>
#ifndef FRANJAHORARIA_H
#define FRANJAHORARIA_H

#ifndef R_H
#define R_H

class FranjaHoraria
{
private:
    int hora;
    int anio;
    int dia;
    int mes;

public:
    
    FranjaHoraria(int h, int a, int d, int me);

    int getHora();
    int getAnio();
    int getDia();
    int getMes();

    void setHora(int h);
    void setAnio(int a);
    void setDia(int d);
    void setMes(int me);

    bool antesDe(const FranjaHoraria &otra);

    bool igualA(const FranjaHoraria &otra);

    int regresarFechanumerica();
};

#endif