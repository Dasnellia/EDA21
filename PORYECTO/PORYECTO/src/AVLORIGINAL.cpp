#include <iostream>
using namespace std;

// Definición del nodo del árbol AVL
struct Nodo {
    int dato;
    int factor_balance;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;

    Nodo(int val) : dato(val), factor_balance(0), izq(nullptr), der(nullptr), padre(nullptr) {}
};

// Clase Árbol AVL
class ArbolAVL {
private:
    Nodo* raiz;

    // Métodos privados
    Nodo* insertarRecursivo(Nodo* nodo, int val);
    int calcularAltura(Nodo* nodo);
    void actualizarFactor(Nodo* nodo);
    Nodo* rebalance(Nodo* nodo);
    Nodo* rotarIzquierda(Nodo* nodo);
    Nodo* rotarDerecha(Nodo* nodo);
    void mostrarEchado(Nodo* nodo, int nivel);

public:
    ArbolAVL() : raiz(nullptr) {}
    void insertar(int val);
    void mostrar();
};

// Método insertar (público)
void ArbolAVL::insertar(int val) {
    raiz = insertarRecursivo(raiz, val);
}

// Inserción recursiva
Nodo* ArbolAVL::insertarRecursivo(Nodo* nodo, int val) {
    if (!nodo) return new Nodo(val);

    if (val < nodo->dato) {
        nodo->izq = insertarRecursivo(nodo->izq, val);
        nodo->izq->padre = nodo;
    } else {
        nodo->der = insertarRecursivo(nodo->der, val);
        nodo->der->padre = nodo;
    }

    // Actualizar balance y rebalancear si es necesario
    actualizarFactor(nodo);
    return rebalance(nodo);
}

// Método para calcular la altura de un nodo
int ArbolAVL::calcularAltura(Nodo* nodo) {
    if (!nodo) return 0;
    return 1 + max(calcularAltura(nodo->izq), calcularAltura(nodo->der));
}

// Actualizar el factor de balance
void ArbolAVL::actualizarFactor(Nodo* nodo) {
    nodo->factor_balance = calcularAltura(nodo->izq) - calcularAltura(nodo->der);
}

// Método de rebalance
Nodo* ArbolAVL::rebalance(Nodo* nodo) {
    actualizarFactor(nodo);

    // Caso: Desbalance por izquierda
    if (nodo->factor_balance > 1) {
        if (nodo->izq && nodo->izq->factor_balance < 0) {
            nodo->izq = rotarIzquierda(nodo->izq);
        }
        return rotarDerecha(nodo);
    }

    // Caso: Desbalance por derecha
    if (nodo->factor_balance < -1) {
        if (nodo->der && nodo->der->factor_balance > 0) {
            nodo->der = rotarDerecha(nodo->der);
        }
        return rotarIzquierda(nodo);
    }

    return nodo;
}

// Rotación a la izquierda
Nodo* ArbolAVL::rotarIzquierda(Nodo* nodo) {
    Nodo* nuevaRaiz = nodo->der;
    nodo->der = nuevaRaiz->izq;
    if (nuevaRaiz->izq) nuevaRaiz->izq->padre = nodo;

    nuevaRaiz->izq = nodo;
    nuevaRaiz->padre = nodo->padre;
    nodo->padre = nuevaRaiz;

    // Actualizar balance
    actualizarFactor(nodo);
    actualizarFactor(nuevaRaiz);

    return nuevaRaiz;
}

// Rotación a la derecha
Nodo* ArbolAVL::rotarDerecha(Nodo* nodo) {
    Nodo* nuevaRaiz = nodo->izq;
    nodo->izq = nuevaRaiz->der;
    if (nuevaRaiz->der) nuevaRaiz->der->padre = nodo;

    nuevaRaiz->der = nodo;
    nuevaRaiz->padre = nodo->padre;
    nodo->padre = nuevaRaiz;

    // Actualizar balance
    actualizarFactor(nodo);
    actualizarFactor(nuevaRaiz);

    return nuevaRaiz;
}

// Mostrar el árbol de forma visual (Echado)
void ArbolAVL::mostrar() {
    if (!raiz) {
        cout << "El árbol está vacío." << endl;
        return;
    }
    mostrarEchado(raiz, 0);
}

void ArbolAVL::mostrarEchado(Nodo* nodo, int nivel) {
    if (nodo) {
        mostrarEchado(nodo->der, nivel + 1);
        for (int i = 0; i < nivel; i++) cout << "    ";
        cout << nodo->dato << " (" << nodo->factor_balance << ")\n";
        mostrarEchado(nodo->izq, nivel + 1);
    }
}

// Función principal
int main() {
    ArbolAVL arbol;
    /*arbol.insertar(40);
    arbol.insertar(20);
    arbol.insertar(10);
    arbol.insertar(25);
    arbol.insertar(30);
    arbol.insertar(22);
    arbol.insertar(50);*/

    /*arbol.insertar(40);
    arbol.insertar(30);
    arbol.insertar(20);*/

    /*arbol.insertar(10);
    arbol.insertar(20);
    arbol.insertar(30);*/

    arbol.insertar(1);
    arbol.insertar(5);
    arbol.insertar(6);
    arbol.insertar(8);
    arbol.insertar(9);
    arbol.insertar(10);
    arbol.insertar(100);


    cout << "Arbol AVL (Visualizado):" << endl;
    arbol.mostrar();

    return 0;
}
