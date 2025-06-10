#ifndef ZONA_H
#define ZONA_H

class Zona
{
private:
    int aforo;
    char ubicacion[50];
    bool lleno;
    int tamanio;

public:
    Zona(int a = 0, const char *ubi = "", int t = 0);

    void mostrarInfo() const;
};

#endif