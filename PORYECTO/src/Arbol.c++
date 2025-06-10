#include <iostream>

using namespace std;

struct Nodo{
    //se crearon los campos:
    int dato;
    Nodo *der;
    Nodo *izq;
    Nodo *padre;//para eliminar un nodo, �ste debe saber qui�n es su padre
};

Nodo *crearNodo(int, Nodo*);//para eliminar se modifica pq queremos saber qui�n es el padre de cada nodo al crear
void insertar(Nodo*&, int , Nodo*);//para eliminar se modifica pq queremos saber qui�n es el padre de cada nodo al insertar
void mostrarArbol(Nodo*, int);
bool busqueda(Nodo*, int n);
void preOrdenArbol(Nodo*);
void InorderArbol(Nodo*);
void PostordenArbol(Nodo*);
void eliminar(Nodo*, int );
void eliminarNodo(Nodo *);
Nodo *nodoMinimo(Nodo *);
void destruirNodo(Nodo *);


int main()
{
    int n;
    Nodo* raiz = NULL;
    do
    {
        cout<<"\Ingrese el dato a insertar en el ABB:";
        cin>>n;
        if(n>-1)
            insertar(raiz, n, NULL);//inserta los nodos pero no el -1
    }while(n >-1);//termina el bucle
    cout<<"\n***Se muestra el arbol ABB***\n";
    mostrarArbol(raiz, 0);
    cout<<"Ingrese el dato a buscar en el ABB:";
    cin>>n;
    cout<<"Se encontro el dato en el ABB?"<<busqueda(raiz, n);
    cout<<"\nRecorrido PreOrden del ABB:\n";
    preOrdenArbol(raiz);
    cout<<"\nRecorrido Inorder del ABB:\n";
    InorderArbol(raiz);
    cout<<"\nRecorrido Postorden del ABB:\n";
    PostordenArbol(raiz);
    cout<<"\nIngrese nodo a eliminar en el ABB:";
    cin>>n;
    eliminar(raiz, n);
    cout<<"\n***Se muestra el arbol ABB***\n";
    mostrarArbol(raiz, 0);
    cout<<"\nRecorrido PreOrden del ABB:\n";
    preOrdenArbol(raiz);
    return 0;
}

//funci�n crear nodo
Nodo *crearNodo(int n, Nodo* padre)
{
    Nodo *nuevo_nodo = new Nodo();
    //se asignan valores a los campos
    nuevo_nodo->dato = n;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->padre = padre;
    return nuevo_nodo;//retorna el puntero_nodo con su dato, hijo izq, hijo derecho
}

void insertar(Nodo*& raiz, int n, Nodo *padre) //par�metros de tipo nodo puntero y referencia para el arbol y el dato a insertar
{
    //cuando el �rbol est� vac�o
    if(raiz == NULL)
    {
        //creamos un nuevo nodo
        Nodo *nuevo_nodo = crearNodo(n, padre);
        raiz = nuevo_nodo;
        // nodo_raiz -> nodo_n
    }
    //cuando el �rbol est� lleno
    else
    {
        //el arbol ya tiene la raiz
        //elementos < raiz (inserta lado izquierdo)
        //elemento > raiz (inserta lado derecho)
        if(n < raiz->dato)
           insertar(raiz->izq, n, raiz);//llamada recursiva
        else
            insertar(raiz->der, n, raiz);
    }
}

void mostrarArbol(Nodo* raiz, int cont)
{
    if(raiz == NULL)
        return;
    else
    {
        mostrarArbol(raiz->der,cont+1);//se muestra todo el lado derecho de la raiz
        for(int i=0; i<cont; i++)
        {
            cout<<"  ";//dar espacios entre nodos
        }
        cout<<raiz->dato<<endl;
        mostrarArbol(raiz->izq,cont+1);//luego se muestra todo el lado izquierdo
    }
}

bool busqueda(Nodo *raiz, int n)
{
    //buscar un elemento en la raiz
     if(raiz == NULL)
            return false;
     else
     {
         if(raiz->dato == n)
            return true;
         else
         {
           if(n < raiz->dato)
               busqueda(raiz->izq, n);//llamada recursiva
           else
                busqueda(raiz->der, n);
         }
     }
}

void preOrdenArbol(Nodo* raiz)
{
    if(raiz == NULL)
        return;
    else
    {
        cout<<raiz->dato<<" - ";
        preOrdenArbol(raiz->izq);
        preOrdenArbol(raiz->der);
    }
}

void InorderArbol(Nodo* raiz)
{
    if(raiz == NULL)
        return;
    else
    {
        InorderArbol(raiz->izq);
        cout<<raiz->dato<<" - ";
        InorderArbol(raiz->der);
    }
}

void PostordenArbol(Nodo* raiz)
{
    if(raiz == NULL)
        return;
    else
    {
        PostordenArbol(raiz->izq);
        PostordenArbol(raiz->der);
        cout<<raiz->dato<<" - ";
    }
}

//funci�n para eliminar un nodo en el arbol
void eliminar(Nodo* raiz, int n)
{
     if(raiz == NULL)
        return;
    else if(n < raiz->dato)
    {
        //si el elemento es menor busca por la izquierda
        eliminar(raiz->izq, n);
    }
    else if(n > raiz->dato)
    {
        //si el elemento es mayor busca por la derecha
        eliminar(raiz->der, n);
    }
    else
    {
        //si ya encontr� el valor
        eliminarNodo(raiz);
    }
}

Nodo *nodoMinimo(Nodo *raiz)
{
    //funci�n para encontrar el nodo de la parte m�s izquierda posible
    if(raiz == NULL)
        return NULL;//si el arbol est� vac�o

    if(raiz->izq != NULL) //si tiene hijo izquierdo
        return nodoMinimo(raiz->izq);//buscamos la parte mas izquierda posible
    else
        //si no tiene hijo izquierdo retornamos el mismo nodo
        return raiz;
}

void reemplazar(Nodo* raiz, Nodo *nuevoNodo)
{
    if(raiz->padre)//si el arbol tiene padre
    {
        //funcion para reemplazar dos nodos
        if(raiz->dato == raiz->padre->izq->dato)
            //raiz->padre hay que asignarle su nuevo hijo
            raiz->padre->izq = nuevoNodo;
        else if(raiz->dato == raiz->padre->der->dato)
            raiz->padre->der = nuevoNodo;
    }
    if(nuevoNodo)//si nuevoNodo existe
    {
        //se asigna a su nuevo padre
        nuevoNodo->padre = raiz->padre;
    }
}

void destruirNodo(Nodo *nodoDestruir)
{
    //funci�n para destruir nodo
    nodoDestruir->izq = NULL;
    nodoDestruir->der = NULL;
    delete nodoDestruir;
}

void eliminarNodo(Nodo *nodoEliminar)
{
    //1. Si el nodoEliminar tiene hijo izquierdo y derecho
    if(nodoEliminar->izq!= NULL && nodoEliminar->der != NULL)
    {
        Nodo *menor = nodoMinimo(nodoEliminar->der);
        nodoEliminar->dato = menor->dato;
        eliminarNodo(menor);
    }
    //2. Si el nodoEliminar tiene 1 hijo izquierdo o 1 hijo derecho
    else if(nodoEliminar->izq!= NULL)
    {
        //2.1 si el nodoEliminar tiene 1 hijo izquierdo
        reemplazar(nodoEliminar, nodoEliminar->izq);
        destruirNodo(nodoEliminar);
    }
    //2. Si el nodoEliminar tiene 1 hijo derecho
    else if(nodoEliminar->der!= NULL)
    {
        //2.1 si el nodoEliminar tiene 1 hijo izquierdo
        reemplazar(nodoEliminar, nodoEliminar->der);
        destruirNodo(nodoEliminar);
    }
    else
    {
        //el nodo no tiene hijos
        reemplazar(nodoEliminar, NULL);
        destruirNodo(nodoEliminar);
    }
}

