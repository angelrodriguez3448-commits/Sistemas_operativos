// Definición de la clase Proceso. Se sobrecargan algunos operadores
// para que objetos de esta clase puedan ser usados de manera directa.
// Esta clase se guarda en la biblioteca "Proceso.h"

#include <iostream>
#include <cstring>

using namespace std;

class Proceso {
private:
    char NomProg[64];
    int Operador;
    int Numero1;
    int Numero2;
    int TiempoME;
    int ID;

public:
    Proceso();
    Proceso(char[], int, int, int, int, int);
    const char* RegresaNombre();
    int RegresaOperador();
    int RegresaNumero(int);
    int RegresaTiempo();
    int RegresaID();
    void CambiarID(int);
    int operator == (Proceso);
    int operator > (Proceso);
    int operator < (Proceso);
    friend istream& operator >> (istream&, Proceso&);
    friend ostream& operator << (ostream&, Proceso&);
};

// Declaración del método constructor por omisión
Proceso::Proceso() {
    // Constructor vacío
}

// Declaración del método constructor con parámetros
Proceso::Proceso(char NomP[], int Oper, int Num1,  int Num2, int Tiempo, int Id) {
    strcpy(NomProg, NomP);
    Operador = Oper;
    Numero1 = Num1;
    Numero2 = Num2;
    TiempoME = Tiempo;
    ID = Id;
}

//Metodo que regresa el valor del atributo NomProg
const char* Proceso::RegresaNombre() {
    return NomProg;
}

//Metodo que regresa el valor del atributo Operador
int Proceso::RegresaOperador() {
    return Operador;
}

// Método que regresa el valor de alguno de los atributos Numero
int Proceso::RegresaNumero(int indice) {
    if (indice == 1)
        return Numero1;
    else
        return Numero2;
}

//Metodo que regresa el valor del atributo TiempoME
int Proceso::RegresaTiempo() {
    return TiempoME;
}

//Metodo que regresa el valor del atributo ID
int Proceso::RegresaID() {
    return ID;
}

//Metodo que cambia el valor del atributo ID
void Proceso::CambiarID(int id){
    ID = id;
}

// Método para comparar si un producto es mayor que otro (clave)
int Proceso::operator > (Proceso Proc) {
    return ID > Proc.ID;
}

// Método para comparar si un producto es menor que otro (clave)
int Proceso::operator < (Proceso Proc) {
    return ID < Proc.ID;
}

// Método para comparar si dos procesos son iguales (ID)
int Proceso::operator == (Proceso Proc) {
    return ID == Proc.ID;
}

// Sobrecarga del operador >> para permitir lectura desde cin
istream& operator >> (istream& Lee, Proceso& ObjProc) {
    cout << "\nIngrese nombre del programador: ";
    Lee >> ObjProc.NomProg;
    cout << "\nSeleccione la operacion a realizar: ";
    cout << "\n\t1. Suma";
    cout << "\n\t2. Resta";
    cout << "\n\t3. Multiplicacion";
    cout << "\n\t4. Division";
    cout << "\n\t5. Residuo";
    cout << "\n\t6. Potencia\n";
    Lee >> ObjProc.Operador;
    while(ObjProc.Operador >= 7 || ObjProc.Operador <= 0){
        cout << "\nValor de operacion no valido";
        cout << "\nSeleccione la operacion a realizar: ";
        Lee >> ObjProc.Operador;
    }
    cout << "\nIngrese el primer numero: ";
    Lee >> ObjProc.Numero1;
    cout << "\nIngrese el segundo numero: ";
    Lee >> ObjProc.Numero2;
    if (ObjProc.Operador == 4 || ObjProc.Operador == 5){
        while (ObjProc.Numero2 == 0){
            cout << "\nValor no valido, para la operacion elegida";
            cout << "\nIngrese el segundo numero: ";
            Lee >> ObjProc.Numero2;
        }
    }
    cout << "\nIngrese el tiempo maximo estimado: ";
    Lee >> ObjProc.TiempoME;
    while (ObjProc.TiempoME <= 0){
        cout << "\nTiempo no valido";
        cout << "\nIngrese el tiempo maximo estimado: ";
        Lee >> ObjProc.TiempoME;
    }
    cout << "\nIngrese el ID del proceso: ";
    Lee >> ObjProc.ID;
    while (ObjProc.ID <= 0){
        cout << "\nID no valido";
        cout << "\nIngrese el ID de programa: ";
        Lee >> ObjProc.ID;
    }
    return Lee;
}

// Sobrecarga del operador << para permitir impresión con cout
ostream& operator << (ostream& Escribe, Proceso& ObjProc) {
    Escribe << "\n\nDatos del proceso\n";
    Escribe << "Nombre del programador: " << ObjProc.NomProg;
    Escribe << "\nOperacion: " << ObjProc.Numero1;
    switch(ObjProc.Operador){
    case 1:
        Escribe << " + ";
        break;
    case 2:
        Escribe << " - ";
        break;
    case 3:
        Escribe << " * ";
        break;
    case 4:
        Escribe << " / ";
        break;
    case 5:
        Escribe << " % ";
        break;
    case 6:
        Escribe << " ^ ";
        break;
    }
    Escribe << ObjProc.Numero2;
    Escribe << "\nID de programa: " << ObjProc.ID << "\n";
    return Escribe;
}


