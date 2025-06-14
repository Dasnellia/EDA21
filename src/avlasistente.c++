#include "avlasistente.h"
#include <iostream>
using namespace std;

NodoAsistente::NodoAsistente(int id) 
    : idasistente(id), asistente(), factor_balance(0), izq(nullptr), der(nullptr), padre(nullptr) {}

ArbolAVL::ArbolAVL() : raiz(nullptr) {}

void ArbolAVL::insertar(int id) {
    raiz = insertarRecursivo(raiz, id);
}

NodoAsistente* ArbolAVL::insertarRecursivo(NodoAsistente* nodo, int id) {
    if (!nodo) return new NodoAsistente(id);

    if (id < nodo->idasistente) {
        nodo->izq = insertarRecursivo(nodo->izq, id);
        nodo->izq->padre = nodo;
    } else {
        nodo->der = insertarRecursivo(nodo->der, id);
        nodo->der->padre = nodo;
    }

    actualizarFactor(nodo);
    return rebalance(nodo);
}

int ArbolAVL::calcularAltura(NodoAsistente* nodo) {
    if (!nodo) return 0;
    return 1 + max(calcularAltura(nodo->izq), calcularAltura(nodo->der));
}

void ArbolAVL::actualizarFactor(NodoAsistente* nodo) {
    nodo->factor_balance = calcularAltura(nodo->izq) - calcularAltura(nodo->der);
}

NodoAsistente* ArbolAVL::rebalance(NodoAsistente* nodo) {
    actualizarFactor(nodo);

    if (nodo->factor_balance > 1) {
        if (nodo->izq && nodo->izq->factor_balance < 0)
            nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (nodo->factor_balance < -1) {
        if (nodo->der && nodo->der->factor_balance > 0)
            nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

NodoAsistente* ArbolAVL::rotarIzquierda(NodoAsistente* nodo) {
    NodoAsistente* nuevaRaiz = nodo->der;
    nodo->der = nuevaRaiz->izq;
    if (nuevaRaiz->izq) nuevaRaiz->izq->padre = nodo;
    nuevaRaiz->izq = nodo;

    nuevaRaiz->padre = nodo->padre;
    nodo->padre = nuevaRaiz;

    actualizarFactor(nodo);
    actualizarFactor(nuevaRaiz);
    return nuevaRaiz;
}

NodoAsistente* ArbolAVL::rotarDerecha(NodoAsistente* nodo) {
    NodoAsistente* nuevaRaiz = nodo->izq;
    nodo->izq = nuevaRaiz->der;
    if (nuevaRaiz->der) nuevaRaiz->der->padre = nodo;
    nuevaRaiz->der = nodo;

    nuevaRaiz->padre = nodo->padre;
    nodo->padre = nuevaRaiz;

    actualizarFactor(nodo);
    actualizarFactor(nuevaRaiz);
    return nuevaRaiz;
}

bool ArbolAVL::registrarAsistenciaPorID(int id) {
    NodoAsistente* actual = raiz;
    while (actual) {
        if (id == actual->idasistente) {
            actual->asistente.RegistrarAsistencia();
            return true;
        }
        actual = (id < actual->idasistente) ? actual->izq : actual->der;
    }
    return false;
}

void ArbolAVL::mostrar() {
    if (!raiz) {
        cout << "El árbol está vacío.\n";
        return;
    }
    mostrarEchado(raiz, 0);
}

void ArbolAVL::mostrarEchado(NodoAsistente* nodo, int nivel) {
    if (nodo) {
        mostrarEchado(nodo->der, nivel + 1);
        for (int i = 0; i < nivel; ++i)
            cout << "    ";
        cout << nodo->idasistente << " | Prioridad: " << nodo->asistente.getPrioridad()
             << " | Asistió: " << (nodo->asistente.getAsistencia() ? "Sí" : "No")
             << " | Balance: " << nodo->factor_balance << "\n";
        mostrarEchado(nodo->izq, nivel + 1);
    }
}

void ArbolAVL::mostrarVIPs(NodoAsistente* nodo) {
    if (!nodo) return;
    mostrarVIPs(nodo->izq);
    if (nodo->asistente.getPrioridad() == 5)
        cout << "ID: " << nodo->idasistente << " (VIP)\n";
    mostrarVIPs(nodo->der);
}

void ArbolAVL::mostrarSoloVIPs() {
    cout << "Asistentes VIP:\n";
    mostrarVIPs(raiz);
}
