#include <iostream>
using namespace std;

// Prototipo de la plantilla de la clase Lista. Así, en la clase
// NodoLista se podrá hacer referencia a ella.
template <class T>
class Lista;

// Definición de la clase NodoLista.
template <class T>
class NodoLista {
private:
    NodoLista<T>* Liga;
    T Info;
    //T* ApunT;

public:
    NodoLista();
    T RegresaInfo();
    NodoLista<T>* RegresaLiga();
    T* RegresaApun();

    friend class Lista<T>;
};

// Declaración del método constructor por omisión. Inicializa con el
// valor NULL al puntero al siguiente nodo.
template <class T>
NodoLista<T>::NodoLista() {
    Liga = NULL;
}

// Método que permite, a usuarios ajenos a la clase, conocer el valor
// del atributo Info.
template <class T>
T NodoLista<T>::RegresaInfo() {
    return Info;
}

// Método que permite, a usuarios ajenos a la clase, conocer la ubicacion
// del atributo Info.
template <class T>
T* NodoLista<T>::RegresaApun() {
    return &Info;
}

// Método que permite, a usuarios ajenos a la clase, conocer el valor
// del atributo Liga.
template <class T>
NodoLista<T>* NodoLista<T>::RegresaLiga() {
    return Liga;
}


/** Definición de la clase Lista **/
template <class T>
class Lista {
private:
    NodoLista<T>* Primero;

public:
    Lista();
    NodoLista<T>* RegresaPrimero();
    void ImprimeRecursivo(NodoLista<T>*);
    void ImprimeUnNodo(NodoLista<T>*);
    void InsertaOrdenCrec(T);
    void InsertaFinal(T);
    int EliminaUnNodo(T);
    NodoLista<T>* BuscaOrdenada(T);
};

/** Constructor **/
template <class T>
Lista<T>::Lista() {
    Primero = nullptr;
}

/** Método que regresa la dirección del primer nodo **/
template <class T>
NodoLista<T>* Lista<T>::RegresaPrimero() {
    return Primero;
}

/** Método que imprime recursivamente los elementos de la lista **/
template <class T>
void Lista<T>::ImprimeRecursivo(NodoLista<T>* P) {
    if (P) {
        std::cout << "\nInformación: " << P->Info;
        ImprimeRecursivo(P->Liga);
    }
    std::cout << '\n';
}

/** Método que imprime un solo nodo **/
template <class T>
void Lista<T>::ImprimeUnNodo(NodoLista<T>* P) {
    if (P)
        std::cout << P->Info;
}

/** Método que inserta un nodo en orden creciente **/
template <class T>
void Lista<T>::InsertaOrdenCrec(T Dato) {
    NodoLista<T>* P, * Q, * Ant;
    if (!Primero || Primero->Info > Dato) {
        // Llama al método InsertaInicio (definido aquí directamente)
        P = new NodoLista<T>();
        P->Info = Dato;
        P->Liga = Primero;
        Primero = P;
    } else {
        Q = Primero;
        while (Q && Q->Info < Dato) {
            Ant = Q;
            Q = Q->Liga;
        }
        P = new NodoLista<T>();
        P->Info = Dato;
        Ant->Liga = P;
        P->Liga = Q;
    }
}

/** Método que elimina un nodo con cierta información **/
template <class T>
int Lista<T>::EliminaUnNodo(T Ref) {
    NodoLista<T>* P = Primero, * Ant = nullptr;
    if (!Primero)
        return -1; // Lista vacía

    while (P && P->Info != Ref/*P && !(P->Info == Ref)*/) {
        Ant = P;
        P = P->Liga;
    }

    if (!P)
        return 0; // No encontrado

    if (!Ant)
        Primero = P->Liga;
    else
        Ant->Liga = P->Liga;

    delete P;
    return 1;
}

/** Método que busca un nodo en una lista ordenada **/
template <class T>
NodoLista<T>* Lista<T>::BuscaOrdenada(T Ref) {
    NodoLista<T>* Q = Primero;
    while (Q && Q->Info < Ref)
        Q = Q->Liga;

    if (Q && Q->Info == Ref)
        return Q;

    return nullptr;
}

/** Método que inserta un nodo al final de la lista **/
template <class T>
void Lista<T>::InsertaFinal(T Dato) {
    NodoLista<T>* P = new NodoLista<T>();
    P->Info = Dato;
    P->Liga = nullptr;

    if (!Primero) {
        Primero = P;
    } else {
        NodoLista<T>* Q = Primero;
        while (Q->Liga) {
            Q = Q->Liga;
        }
        Q->Liga = P;
    }
}
