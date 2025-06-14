#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "asistente.h"

struct NodoAsistente {
    int idasistente;
    Asistente asistente;
    int factor_balance;
    NodoAsistente* izq;
    NodoAsistente* der;
    NodoAsistente* padre;

    NodoAsistente(int id);
};

class ArbolAVL {
private:
    NodoAsistente* raiz;

    NodoAsistente* insertarRecursivo(NodoAsistente* nodo, int id);
    void actualizarFactor(NodoAsistente* nodo);
    int calcularAltura(NodoAsistente* nodo);
    NodoAsistente* rebalance(NodoAsistente* nodo);
    NodoAsistente* rotarIzquierda(NodoAsistente* nodo);
    NodoAsistente* rotarDerecha(NodoAsistente* nodo);
    void mostrarEchado(NodoAsistente* nodo, int nivel);
    void mostrarVIPs(NodoAsistente* nodo);

public:
    ArbolAVL();
    void insertar(int id);
    bool registrarAsistenciaPorID(int id);
    void mostrar() const;
    void mostrarSoloVIPs() const;
};

#endif
