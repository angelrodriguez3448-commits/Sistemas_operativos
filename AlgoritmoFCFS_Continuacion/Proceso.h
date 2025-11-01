// Definición de la clase Proceso. Se sobrecargan algunos operadores
// para que objetos de esta clase puedan ser usados de manera directa.
// Esta clase se guarda en la biblioteca "Proceso.h"

#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

class Proceso {
private:
    int ID;
    int Operador;
    int Numero1;
    int Numero2;
    int Tiempo;
    int TiempoTrans;
    int TiempoBloq;
    int TiempoLlega;
    int TiempoFin;
    int TiempoRes;
    bool Error;
    bool Bloqueo;

public:
    //Constructores
    Proceso();
    Proceso(int, int, int, int, int);

    //Destructor
    ~Proceso();

    //Metodos para el manejo de los atributos
    int RegresaOperador();
    int RegresaNumero(int);
    int RegresaTiempo();
    int RegresaTiempoTrans();
    void CambiarTiempo(int);
    int RegresaID();
    void CambiarID(int);
    bool RegresaError();
    void CambiarError(bool);
    void CambiarTiempoB(int);
    int RegresaTiempoB();
    void CambiarTiempoLl(int);
    int RegresaTiempoLl();
    void CambiarTiempoF(int);
    int RegresaTiempoF();
    void CambiarTiempoR(int);
    int RegresaTiempoR();
    bool RegresaBloq();
    void CambiarBloq(bool);

    //Metodos auxiliares
    int operator == (Proceso);
    int operator != (Proceso);
    int operator > (Proceso);
    int operator < (Proceso);
    friend ostream& operator << (ostream&, Proceso&);
};

// Declaración del método constructor por omisión
Proceso::Proceso() {
    // Constructor vacío
}

// Declaración del método constructor con parámetros
Proceso::Proceso(int Oper, int Num1,  int Num2, int Tiemp, int Id) {
    Operador = Oper;
    Numero1 = Num1;
    Numero2 = Num2;
    Tiempo = Tiemp;
    ID = Id;
    TiempoLlega = -1;
    TiempoTrans = 0;
    TiempoBloq = 0;
    TiempoRes = -1;
    TiempoFin = 0;
}

// Declaración del método destructor
Proceso::~Proceso(){
    // Destructor vacio
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

//Metodo que regresa el valor del atributo Tiempo
int Proceso::RegresaTiempo() {
    return Tiempo;
}

//Metodo que regresa el valor del atributo Tiempo transcurrido
int Proceso::RegresaTiempoTrans() {
    return TiempoTrans;
}

//Metodo que cambia el valor del atributo Tiempo transcurrido
void Proceso::CambiarTiempo(int tiempo){
    TiempoTrans = tiempo;
}

//Metodo que regresa el valor del atributo ID
int Proceso::RegresaID() {
    return ID;
}

//Metodo que cambia el valor del atributo ID
void Proceso::CambiarID(int id){
    ID = id;
}

//Metodo que regresa el valor del atributo Error
bool Proceso::RegresaError() {
    return Error;
}

//Metodo que cambia el valor del atributo Error
void Proceso::CambiarError(bool error){
    Error = error;
}

//Metodo que regresa el valor del atributo Tiempo bloquedado
int Proceso::RegresaTiempoB() {
    return TiempoBloq;
}

//Metodo que cambia el valor del atributo Tiempo bloqueado
void Proceso::CambiarTiempoB(int tiempo){
    TiempoBloq = tiempo;
}

//Metodo que regresa el valor del atributo Tiempo Llegada
int Proceso::RegresaTiempoLl() {
    return TiempoLlega;
}

//Metodo que cambia el valor del atributo Tiempo Llegada
void Proceso::CambiarTiempoLl(int tiempo){
    TiempoLlega = tiempo;
}

//Metodo que regresa el valor del atributo Tiempo Finalizacion
int Proceso::RegresaTiempoF() {
    return TiempoFin;
}

//Metodo que cambia el valor del atributo Tiempo Finalizacion
void Proceso::CambiarTiempoF(int tiempo){
    TiempoFin = tiempo;
}

//Metodo que regresa el valor del atributo Tiempo Respuesta
int Proceso::RegresaTiempoR() {
    return TiempoRes;
}

//Metodo que cambia el valor del atributo Tiempo Respuesta
void Proceso::CambiarTiempoR(int tiempo){
    TiempoRes = tiempo;
}

//Metodo que regresa el valor del atributo Bloqueo
bool Proceso::RegresaBloq() {
    return Bloqueo;
}

//Metodo que cambia el valor del atributo Bloqueo
void Proceso::CambiarBloq(bool bloq){
    Bloqueo = bloq;
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

//Método que permite comparar dos procesos para determinar si son distintos.
int Proceso::operator != (Proceso Proc)
{
    int Resp = 0;
    if (ID != Proc.ID) Resp = 1;
    return Resp;
}

// Sobrecarga del operador << para permitir impresión con cout
ostream& operator << (ostream& Escribe, Proceso& ObjProc) {
    Escribe << "\n\nDatos del proceso\n";
    Escribe << "ID del proceso: " << ObjProc.ID;
    Escribe << "\tOperacion: " << ObjProc.Numero1;
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
    return Escribe;
}


