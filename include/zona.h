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

    int getAforo() const;
    const char *getUbicacion() const;
    bool isLleno() const;
    int getTamanio() const;

    void setAforo(int a);
    void setUbicacion(const char *ubi);

    void setLleno(bool estado);
    void setTamanio(int t);
    bool esDisponible(int fechaID, int duracionHoras) const;

};

#endif