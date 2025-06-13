#include <iostream>
using namespace std;
#include "./include/asistente.h"
#include "Franjahoraria.h"

// este se encuentra dentro de evento
struct NodoAsistente
{
    int idasistente;
    Asistente Asistente;
    NodoAsistente *izq;
    NodoAsistente *der;
    NodoAsistente *padre;

    NodoAsistente(int val)
    : idasistente(val),
      Asistente(),  // Asistente vacío, se puede sobrescribir luego si quieres
      factor_balance(0),
      izq(nullptr), der(nullptr), padre(nullptr) {}

};

// Clase �rbol AVL
class ArbolAVL
{
private:
    NodoAsistente *raiz;

    // M�todos privados
    NodoAsistente *insertarRecursivo(NodoAsistente *NodoAsistente, int val);
    int calcularAltura(NodoAsistente *NodoAsistente);
    void actualizarFactor(NodoAsistente *NodoAsistente);
    NodoAsistente *rebalance(NodoAsistente *NodoAsistente);
    NodoAsistente *rotarIzquierda(NodoAsistente *NodoAsistente);
    NodoAsistente *rotarDerecha(NodoAsistente *NodoAsistente);
    void mostrarEchado(NodoAsistente *NodoAsistente, int nivel);

public:
    ArbolAVL() : raiz(nullptr) {}
    void insertar(int val);
    void mostrar();
};

// M�todo insertar (p�blico)
void insertar(const Asistente& nuevo) {
    raiz = insertarRecursivo(raiz, nuevo);
}


// Inserci�n recursiva
NodoAsistente *ArbolAVL::insertarRecursivo(NodoAsistente *NodoAsistente, int val)
{
    if (!NodoAsistente)
        return new NodoAsistente(val);

    if (val < NodoAsistente->idasistente)
    {
        NodoAsistente->izq = insertarRecursivo(NodoAsistente->izq, val);
        NodoAsistente->izq->padre = NodoAsistente;
    }
    else
    {
        NodoAsistente->der = insertarRecursivo(NodoAsistente->der, val);
        NodoAsistente->der->padre = NodoAsistente;
    }

    // Actualizar balance y rebalancear si es necesario
    actualizarFactor(NodoAsistente);
    return rebalance(NodoAsistente);
}

// M�todo para calcular la altura de un NodoAsistente
int ArbolAVL::calcularAltura(NodoAsistente *NodoAsistente)
{
    if (!NodoAsistente)
        return 0;
    return 1 + max(calcularAltura(NodoAsistente->izq), calcularAltura(NodoAsistente->der));
}

// Actualizar el factor de balance
void ArbolAVL::actualizarFactor(NodoAsistente *NodoAsistente)
{
    NodoAsistente->factor_balance = calcularAltura(NodoAsistente->izq) - calcularAltura(NodoAsistente->der);
}

// M�todo de rebalance
NodoAsistente *ArbolAVL::rebalance(NodoAsistente *NodoAsistente)
{
    actualizarFactor(NodoAsistente);

    // Caso: Desbalance por izquierda
    if (NodoAsistente->factor_balance > 1)
    {
        if (NodoAsistente->izq && NodoAsistente->izq->factor_balance < 0)
        {
            NodoAsistente->izq = rotarIzquierda(NodoAsistente->izq);
        }
        return rotarDerecha(NodoAsistente);
    }

    // Caso: Desbalance por derecha
    if (NodoAsistente->factor_balance < -1)
    {
        if (NodoAsistente->der && NodoAsistente->der->factor_balance > 0)
        {
            NodoAsistente->der = rotarDerecha(NodoAsistente->der);
        }
        return rotarIzquierda(NodoAsistente);
    }

    return NodoAsistente;
}

// Rotaci�n a la izquierda
NodoAsistente *ArbolAVL::rotarIzquierda(NodoAsistente *NodoAsistente)
{
    NodoAsistente *nuevaRaiz = NodoAsistente->der;
    NodoAsistente->der = nuevaRaiz->izq;
    if (nuevaRaiz->izq)
        nuevaRaiz->izq->padre = NodoAsistente;

    nuevaRaiz->izq = NodoAsistente;
    nuevaRaiz->padre = NodoAsistente->padre;
    NodoAsistente->padre = nuevaRaiz;

    // Actualizar balance
    actualizarFactor(NodoAsistente);
    actualizarFactor(nuevaRaiz);

    return nuevaRaiz;
}

// Rotaci�n a la derecha
NodoAsistente *ArbolAVL::rotarDerecha(NodoAsistente *NodoAsistente)
{
    NodoAsistente *nuevaRaiz = NodoAsistente->izq;
    NodoAsistente->izq = nuevaRaiz->der;
    if (nuevaRaiz->der)
        nuevaRaiz->der->padre = NodoAsistente;

    nuevaRaiz->der = NodoAsistente;
    nuevaRaiz->padre = NodoAsistente->padre;
    NodoAsistente->padre = nuevaRaiz;

    // Actualizar balance
    actualizarFactor(NodoAsistente);
    actualizarFactor(nuevaRaiz);

    return nuevaRaiz;
}

// Mostrar el �rbol de forma visual (Echado)
void ArbolAVL::mostrar()
{
    if (!raiz)
    {
        cout << "El �rbol est� vac�o." << endl;
        return;
    }
    mostrarEchado(raiz, 0);
}

void ArbolAVL::mostrarEchado(NodoAsistente *NodoAsistente, int nivel)
{
    if (NodoAsistente)
    {
        mostrarEchado(NodoAsistente->der, nivel + 1);
        for (int i = 0; i < nivel; i++)
            cout << NodoAsistente->idasistente
                 << " | Prioridad: " << NodoAsistente->Asistente1.getPrioridad()
                 << " | Asistió: " << (NodoAsistente->Asistente1.getAsistencia() ? "Sí" : "No") << endl;

        cout << NodoAsistente->idasistente << " (" << NodoAsistente->factor_balance << ")\n";
        mostrarEchado(NodoAsistente->izq, nivel + 1);
    }
}

bool registrarAsistenciaPorID(int id) {
    NodoAsistente* actual = raiz;
    while (actual) {
        if (id == actual->idasistente) {
            actual->Asistente1.RegistrarAsistencia();
            return true;
        }
        actual = (id < actual->idasistente) ? actual->izq : actual->der;
    }
    return false; 
}

void mostrarVIPs(NodoAsistente* nodo) const {
    if (!nodo) return;

    mostrarVIPs(nodo->izq);

    if (nodo->Asistente1.getPrioridad() == 5) {
        cout << "ID: " << nodo->idasistente << " (VIP)\n";
    }

    mostrarVIPs(nodo->der);
}

void mostrarSoloVIPs() const {
    cout << "Asistentes VIP:\n";
    mostrarVIPs(raiz);
}


int main()
{

    if (arbol.registrarAsistenciaPorID(5))
    cout << "Asistencia registrada para el ID 5\n";
else
    cout << "No se encontró al asistente\n";

}
