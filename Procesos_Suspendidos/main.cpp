//Angel Ariel Rodriguez Arellano
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <string>
#include <fstream>
#include "Lista.h"
#include "Proceso.h"
#include "Marco.h"
using namespace std;

void imprimirDatos(Proceso ObjProc){
    float ResulProc;
    cout << left << setw(4)  << ObjProc.RegresaID();
    cout << left << setw(4) << ObjProc.RegresaNumero(1);
    switch(ObjProc.RegresaOperador()){
    case 1:
        cout << "+ ";
        ResulProc = ObjProc.RegresaNumero(1) + ObjProc.RegresaNumero(2);
        break;
    case 2:
        cout << "- ";
        ResulProc = ObjProc.RegresaNumero(1) - ObjProc.RegresaNumero(2);
        break;
    case 3:
        cout << "* ";
        ResulProc = ObjProc.RegresaNumero(1) * ObjProc.RegresaNumero(2);
        break;
    case 4:
        cout << "/ ";
        ResulProc = ObjProc.RegresaNumero(1) / ObjProc.RegresaNumero(2);
        break;
    case 5:
        cout << "% ";
        ResulProc = ObjProc.RegresaNumero(1) % ObjProc.RegresaNumero(2);
        break;
    case 6:
        cout << "^ ";
        ResulProc = pow(ObjProc.RegresaNumero(1), ObjProc.RegresaNumero(2));
        break;
    }
    cout << left << setw(5) << ObjProc.RegresaNumero(2);
    if (ObjProc.RegresaError() != true){
        if (ObjProc.RegresaTiempoTrans() == ObjProc.RegresaTiempo()){
            cout << left << setw(10) << ResulProc;
        } else{
            cout << left << setw(10) << "Null";
        }

    } else {
        cout << left << setw(10) << "Error";
    }
}

void imprimirTiempos(Proceso ObjProc, int TG){
    //Tiempo de llegada
    if (ObjProc.RegresaTiempoLl() != -1){
        cout << left << setw(16) << ObjProc.RegresaTiempoLl();
    } else{
        cout << left << setw(16) << "x";
    }
    //Tiempo de Finalizacion
    if(ObjProc.RegresaTiempoF() != 0){
        cout << left << setw(16) << ObjProc.RegresaTiempoF();
    } else{
        cout << left << setw(16) << "x";
    }
    //Tiempo de retorno
    if((ObjProc.RegresaTiempoF() - ObjProc.RegresaTiempoLl()) > 0 && ObjProc.RegresaTiempoLl() != -1){
        cout << left << setw(16) << (ObjProc.RegresaTiempoF() - ObjProc.RegresaTiempoLl());
    } else{
        cout << left << setw(16) << "x";
    }
    //Tiempo de respuesta
    if(ObjProc.RegresaTiempoR() != -1){
        cout << left << setw(16) << ObjProc.RegresaTiempoR();
    } else{
        cout << left << setw(16) << "x";
    }
    //Tiempo de espera
    /*if(ObjProc.RegresaID() == 1){
        cout << left << setw(16) << "0";
    } else*/ if(ObjProc.RegresaTiempoLl() < 0){
        cout << left << setw(16) << "x";
    } else if(ObjProc.RegresaTiempoF() != 0){
        cout << left << setw(16) << (ObjProc.RegresaTiempoF() - ObjProc.RegresaTiempoLl()) - ObjProc.RegresaTiempoTrans();
    } else{
        cout << left << setw(16)<< (TG - ObjProc.RegresaTiempoLl()) - ObjProc.RegresaTiempoTrans();
    }

    if(ObjProc.RegresaTiempoTrans() > 0){
        cout << left << setw(16) << ObjProc.RegresaTiempoTrans();
    } else{
        cout << left << setw(16) << "x";
    }
    cout << "\n";
}

//Funcion para imprimir la memoria
void ImprimirMemoria(Marco Memoria[24][2]){
    cout << "\n";
    //Encabezado de la memoria
    for (int i = 0; i < 2; i ++){
        cout << left << setw(4) << "IdM";
        cout << left << setw(10) << "EspacioM";
        cout << left << setw(6) << "IdP";
        cout << left << setw(6) << "N_Pag";
        cout << left << setw(6) << "Estado";
        if(i == 0){
            cout << "\t";
        } else{
            cout << "\n";
        }
    }

    //Contenido de la memoria
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 24; j++){
            cout << left << setw(4) <<Memoria[j][i].RegresaIdMarco();
            for(int k = 0; k < Memoria[j][i].RegresaCamposO(); k++){
                cout << "* ";
            };
            for(int k = 0; k < Memoria[j][i].RegresaCamposV(); k++){
                cout << "_ ";
            };
            if(Memoria[j][i].RegresaSO() == true){
                cout << "S.O. ";
                cout << left << setw(13) << " ";
            } else{

                //Confirmar si el marco tiene un ID de proceso asignado
                if(Memoria[j][i].RegresaIdProc() == 0){
                    cout << left << setw(6) << "NULL";
                } else{
                    cout << left << setw(6) << Memoria[j][i].RegresaIdProc();
                }

                //Confirmar si el marco tiene un Num de paginas asignado
                if(Memoria[j][i].RegresaPagina() == 0){
                    cout << left << setw(6) << "NULL";
                } else{
                    cout << left << setw(6) << Memoria[j][i].RegresaPagina();
                }

                //Confirmar si el marco tiene un Num de paginas asignado
                if(Memoria[j][i].RegresaEstadoProc() == 'X'){
                    cout << left << setw(6) << "NULL";
                } else{
                    cout << left << setw(6) << Memoria[j][i].RegresaEstadoProc();
                }
            }
            if((j % 2) == 1){
                cout << "\n";
            } else {
                cout << "\t";
            }
        }
    }
}

//Funcion para asignar marcos
bool AsignarPaginas(Marco Memoria[24][2], Proceso &proc){
    int paginasNecesarias = proc.RegresaPaginas();
    int paginasAsignadas = 0;

    //Recorrer la memoria para asignar marcos
    for(int i = 0; i < 2 && paginasAsignadas < paginasNecesarias; i++){
        for(int j = 0; j < 24 && paginasAsignadas < paginasNecesarias; j++){

            //Se selecciona solo los marcos que no tengan asignado SO y un IdProc == 0
            if(Memoria[j][i].RegresaSO() != true && Memoria[j][i].RegresaIdProc() == 0){
                Memoria[j][i].CambiarIdProc(proc.RegresaID());
                Memoria[j][i].CambiarEstadoProc('L');
                paginasAsignadas++;
                Memoria[j][i].CambiarPagina(paginasAsignadas);

                //Asignar el tamaño de campos ocupados y vacios
                if(paginasAsignadas == paginasNecesarias){
                    Memoria[j][i].CambiarCamposO(proc.RegresaUltimaPagi());
                    Memoria[j][i].CambiarCamposV(5 - proc.RegresaUltimaPagi());
                } else{
                    Memoria[j][i].CambiarCamposO(5);
                    Memoria[j][i].CambiarCamposV(0);
                }
            }
        }
    }

    //Si ya se asignaron todos los marcos necesarios retornar true, sino revertir los cambios y retornar false
    if(paginasAsignadas == paginasNecesarias){
        return true;
    } else{
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 24; j++){
                if(!Memoria[j][i].RegresaSO() && Memoria[j][i].RegresaIdProc() == proc.RegresaID()){
                    Memoria[j][i].CambiarIdProc(0);
                    Memoria[j][i].CambiarEstadoProc('X');
                    Memoria[j][i].CambiarCamposO(0);
                    Memoria[j][i].CambiarCamposV(5);
                    Memoria[j][i].CambiarPagina(0);
                }
            }
        }
        return false;
    }
}

//Funcion para liberar marcos asginados a un proceso
void LiberarPaginas(Marco Memoria[24][2], int procID){
    //Recorrer la memoria para liberar marcos
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 24; j++){
            if(Memoria[j][i].RegresaIdProc() == procID){
                Memoria[j][i].CambiarIdProc(0);
                Memoria[j][i].CambiarEstadoProc('X');
                Memoria[j][i].CambiarCamposO(0);
                Memoria[j][i].CambiarCamposV(5);
                Memoria[j][i].CambiarPagina(0);
            }
        }
    }
}

void BuscarEnMemoria(Marco Memoria[24][2], int procID, int Ubicacion[][2], int paginas){
    int i, j;
    for(i = 0; i < 2; i++){
        for(j = 0; j <paginas; j++){
            Ubicacion[j][i] = -1;
        }
    }
    int matPosY = 0;
    for(i = 0; i < 2; i++){
        for(j = 0; j < 24; j++){
            if(Memoria[j][i].RegresaIdProc() == procID){
                Ubicacion[matPosY][0] = j;
                Ubicacion[matPosY][1] = i;
                matPosY++;
            }
        }
    }
}

void CambiarEstadoM(Marco Memoria[24][2], int Ubicacion[][2], int paginas, char estado){
    for(int k = 0; k < paginas; k++){
        int fila = Ubicacion[k][0];
        int col = Ubicacion[k][1];

        if (fila != -1 && col != -1){
            Memoria[fila][col].CambiarEstadoProc(estado);
        }
    }
}

bool Guardar(Proceso ObjProc, const string archivo, bool Reiniciar){
    ofstream proc_suspendidos; //Archivo logico
    if(Reiniciar == true){
        proc_suspendidos.open(archivo, ios::out | ios::trunc); //Reinicia el archivo
    } else{
        proc_suspendidos.open(archivo, ios::app);
    }
    if(!proc_suspendidos){
        cout << "El archivo no se ha creado\n";
        return false;
    } else{
        //cout << "Suspendiendo proceso\n";
        //Guardamos lo datos del proceso
        proc_suspendidos <<
            ObjProc.RegresaID() << ' ' <<
            ObjProc.RegresaOperador() << ' ' <<
            ObjProc.RegresaNumero(1) << ' ' <<
            ObjProc.RegresaNumero(2) << ' ' <<
            ObjProc.RegresaTiempo() << ' ' <<
            ObjProc.RegresaTamanio() << ' ' <<
            ObjProc.RegresaPaginas() << ' ' <<
            ObjProc.RegresaUltimaPagi() << ' ' <<
            ObjProc.RegresaTiempoTrans() << ' ' <<
            //ObjProc.RegresaTiempoB() << ' ' <<
            ObjProc.RegresaTiempoLl() << ' ' <<
            ObjProc.RegresaTiempoR() << ' ' << endl;
    }
    proc_suspendidos.close();
    return true;
}

Proceso Recuperar(const string archivo){
    ifstream proc_suspendidos; //Archivo logico
    proc_suspendidos.open("proc_suspendidos.txt", ios::in);
    Proceso Obj;
    string linea;

    if(!proc_suspendidos){
        cout << "El archivo no se ha creado\n";
        return Obj;
    }
    if(!getline(proc_suspendidos, linea)){
        cout << "Archivo vacio\n";
        return Obj;
    }

    stringstream linea_flujo(linea);
    int IdS, Oper, Num1, Num2, Tiemp, Tam, PgS, UPS, TTrans, TLLS, TRS;

    //cout << "Regresa proceso\n";
    //Guardamos lo datos del proceso
    linea_flujo >>
        IdS >>
        Oper >>
        Num1>>
        Num2 >>
        Tiemp >>
        Tam >>
        PgS >>
        UPS >>
        TTrans >>
        TLLS >>
        TRS;

    Obj.CambiarID(IdS);
    Obj.CambiarOp(Oper);
    Obj.CambiarNum(1, Num1);
    Obj.CambiarNum(2, Num2);
    Obj.CambiarT(Tiemp);
    Obj.CambiarTamanio(Tam);
    Obj.CambiarPaginas(PgS);
    Obj.CambiarUltimaPagi(UPS);
    Obj.CambiarTiempo(TTrans);
    Obj.CambiarTiempoLl(TLLS);
    Obj.CambiarTiempoR(TRS);
    Obj.CambiarTiempoF(0);
    return Obj;
}

void CopiarMenosPrimero(const string archivo){
    ifstream in(archivo);
    ofstream out("temp.txt");

    string linea;
    bool salto = false;

    while(getline(in, linea)){
        if(!salto){
            salto = true; //Saltar el primer registro
            continue;
        }
        out << linea << endl;
    }

    in.close();
    out.close();

    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());
}

void ImprimirPorcesosSuspendidos(const string archivo, int TG){
    ifstream proc_suspendidos; //Archivo logico
    proc_suspendidos.open("proc_suspendidos.txt", ios::in);

    if(!proc_suspendidos){
        cout << "El archivo no se ha creado\n";
        return;
    }

    int IdS, Oper, Num1, Num2, Tiemp, Tam, PgS, UPS, TTrans, TLLS, TRS;

    while(proc_suspendidos >>
            IdS >>
            Oper >>
            Num1>>
            Num2 >>
            Tiemp >>
            Tam >>
            PgS >>
            UPS >>
            TTrans >>
            TLLS >>
            TRS){
        Proceso Obj;

        Obj.CambiarID(IdS);
        Obj.CambiarOp(Oper);
        Obj.CambiarNum(1, Num1);
        Obj.CambiarNum(2, Num2);
        Obj.CambiarT(Tiemp);
        Obj.CambiarTamanio(Tam);
        Obj.CambiarPaginas(PgS);
        Obj.CambiarUltimaPagi(UPS);
        Obj.CambiarTiempo(TTrans);
        Obj.CambiarTiempoLl(TLLS);
        Obj.CambiarTiempoR(TRS);
        Obj.CambiarTiempoF(0);

        imprimirDatos(Obj);
        cout << left << setw(10) << "Suspendido";
        imprimirTiempos(Obj, TG);
    }
    proc_suspendidos.close();
    return;
}

int main(){
    cout << "--Simulador de procesos suspendidos--\n\n";
    Marco Memoria [24][2];
    Lista<Proceso> ListaNuevos;
    Lista<Proceso> ListaListos;
    Lista<Proceso> ListaEjecucion;
    Lista<Proceso> ListaTerminados;
    Lista<Proceso> ListaBloqueados;
    NodoLista<Proceso>* AuxiliarListos;
    NodoLista<Proceso>* AuxiliarEjec;
    NodoLista<Proceso>* AuxiliarResul;
    NodoLista<Proceso>* AuxiliarBloq;
    NodoLista<Proceso>* AuxiliarBCP;
    NodoLista<Proceso>* ObjSig;
    Proceso ObjProc;
    Proceso* PObjProc;
    int Oper, Num1, Num2, Tiemp, Id, Tam; //Variables para la creacion de procesos
    Id = 0;
    int NumProcs, i, j, interrupcion, EspaciosLL, EspaciosVas, ProcTer, ProcR, ProcS, IdN, PagN, TiempG, Quantum; //Variables usadas en el ciclo principal
    float ResulProc;
    string archivo = "proc_suspendidos.txt";
    srand(time(NULL));
    bool NuevoVacio;
    bool BanderaError = false;
    bool BanderaBloqueado = false;
    bool BanderaSuspendido = false;
    bool BanderaRegresa = false;
    bool Terminado = false;
    bool Reiniciar = false;
    bool SO;

    fstream proc_suspendidos; //Archivo logico

    //Solicitud de procesos
    do{
        cout << "\nIngrese el numero de procesos que se realizaran: ";
        cin >> NumProcs;
    } while (NumProcs <= 0);

    //Solicitud del Quantum
    do{
        cout << "\nIngrese la cantidad de Quantum: ";
        cin >> Quantum;
    } while (Quantum <= 0);

    //Ciclo para rellenar la memoria con marcos vacios
    for(i = 0; i < 2; i++){
        for(j = 0; j < 24; j++){
            if(i == 1 && j >= 20){
                SO = true;
            } else{
                SO = false;
            }
            Memoria[j][i] = Marco(Id, SO);
            Id++;
        }
    }

    system("cls");

    ImprimirMemoria(Memoria);

    Id = 0;

    //Ciclo para rellenar la lista de procesos
    for (i = 1; i <= NumProcs; i++){
        do{
            Oper = rand() % 7; //Genera valores del 0 al 6
        }while(Oper == 0); //Valida que el operador no sea 0
        Num1 = rand() % 1001; //Genera valores del 0 al 1000
        do{
            Num2 = rand() % 1001;
        }while(Num2 == 0 && (Oper == 4 || Oper == 5)); //Valida que el segundo operando no sea 0 cuando se va a realizar una division o residuo
        do{
            Tiemp = rand() % 21; //Genera valores del 0 al 20
        } while(Tiemp < 4); //Valida que el TME no sea menor a 5
        Id++;
        do{
            Tam = rand() %31; //Genera valores del 0 al 30
        } while(Tam <= 5); //Valida que el Tamanio no sea menor a 6
        Proceso ObjProc(Oper, Num1, Num2, Tiemp, Id, Tam);
        ListaNuevos.InsertaOrdenCrec(ObjProc);
    }
    NuevoVacio = false;

    AuxiliarListos = ListaNuevos.RegresaPrimero();
    ProcR = NumProcs;
    ProcS = 0;
    ProcTer = 0;
    TiempG = 0;
    EspaciosLL = 0;
    EspaciosVas = 44; //44 espacios disponibles en memoria para procesos


    //Ciclo principal
    do{
        //Detectar si se a pulsado una tecla
        if(kbhit() != 0){
            char tecla = getch();
            interrupcion = 0;

            if (tecla == 'e' || tecla == 'E'){
                interrupcion = 1;
            }else if(tecla == 'w' || tecla == 'W'){
                interrupcion = 2;
            }else if(tecla == 'p' || tecla == 'P'){
                interrupcion = 3;
            }else if(tecla == 'c' || tecla == 'C'){
                interrupcion = 4;
            } else if(tecla == 'n' || tecla == 'N'){
                interrupcion = 5;
            } else if(tecla == 'b' || tecla == 'B'){
                interrupcion = 6;
            } else if(tecla == 't' || tecla == 'T'){
                interrupcion = 7;
            } else if (tecla == 's' || tecla == 'S'){
                interrupcion = 8;
            } else if (tecla == 'r' || tecla == 'R'){
                interrupcion = 9;
            }

            //Switch para evaluar interrupciones
            switch(interrupcion){
            case 1:
                //Bloquear
                BanderaBloqueado = true;
                break;
            case 2:
                //Error
                BanderaError = true;
                break;
            case 3:
                //Pausa
                cout << "Pausa, pulsa C para continuar\n";
                do{
                    if(kbhit() != 0){
                        char tecla = getch();
                        interrupcion = 0;

                        if(tecla == 'c' || tecla == 'C'){
                            interrupcion = 4;
                        }
                    }
                }while(interrupcion != 4);
                break;
            case 4:
                //Continuar no hace nada afuera de Puasa
                break;
            case 5:{
                //Crear nuevo proceso
                NumProcs++;
                ProcR++;
                NuevoVacio = false;
                //cout << EspaciosLL;
                do{
                    Oper = rand() % 7; //Genera valores del 0 al 6
                }while(Oper == 0); //Valida que el operador no sea 0
                Num1 = rand() % 1001; //Genera valores del 0 al 1000
                do{
                    Num2 = rand() % 1001;
                }while(Num2 == 0 && (Oper == 4 || Oper == 5)); //Valida que el segundo operando no sea 0 cuando se va a realizar una division o residuo
                do{
                    Tiemp = rand() % 21; //Genera valores del 0 al 20
                } while(Tiemp < 4); //Valida que el TME no sea menor a 5
                Id++;
                do{
                    Tam = rand() %31; //Genera valores del 0 al 30
                } while(Tam <= 5); //Valida que el Tamanio no sea menor a 6
                Proceso ObjProc(Oper, Num1, Num2, Tiemp, Id, Tam);
                ListaNuevos.InsertaOrdenCrec(ObjProc);
                break;
            }
            case 6:
                //Mostrar tabla BCP
                system("cls");
                cout << "Pausa, pulsa C para continuar\n";
                cout << left << setw(4)  << "ID"
                        << setw(11) << "Operacion"
                        << setw(10) << "Resultado"
                        << setw(10) << "Estado"
                        << setw(16) << "T Llegada"
                        << setw(16) << "T Finalizacion"
                        << setw(16) << "T Retorno"
                        << setw(16) << "T Respuesta"
                        << setw(16) << "T Espera"
                        << setw(16) << "T Servicio"
                        << "\n";

                // --- Mostrar todos los procesos agrupados por estado ---
                // 1 Procesos nuevos
                AuxiliarBCP = ListaNuevos.RegresaPrimero();
                while (AuxiliarBCP != NULL) {
                    ObjProc = AuxiliarBCP->RegresaInfo();
                    imprimirDatos(ObjProc);
                    cout << left << setw(10) << "Nuevo";
                    imprimirTiempos(ObjProc, TiempG);
                    AuxiliarBCP = AuxiliarBCP->RegresaLiga();
                }

                // 2️ Procesos listos
                AuxiliarBCP = ListaListos.RegresaPrimero();
                while (AuxiliarBCP != NULL) {
                    ObjProc = AuxiliarBCP->RegresaInfo();
                    imprimirDatos(ObjProc);
                    if (AuxiliarBCP == ListaListos.RegresaPrimero()) {
                        cout << left << setw(10) << "Ejecucion"; // El primero está en ejecución
                    } else {
                        cout << left << setw(10) << "Listo";
                    }
                    imprimirTiempos(ObjProc, TiempG);
                    AuxiliarBCP = AuxiliarBCP->RegresaLiga();
                }

                // 3️ Procesos bloqueados
                AuxiliarBCP = ListaBloqueados.RegresaPrimero();
                while (AuxiliarBCP != NULL) {
                    ObjProc = AuxiliarBCP->RegresaInfo();
                    imprimirDatos(ObjProc);
                    cout << left << setw(10) << "Bloqueado";
                    imprimirTiempos(ObjProc, TiempG);
                    AuxiliarBCP = AuxiliarBCP->RegresaLiga();
                }

                // 4 Procesos suspendidos
                ImprimirPorcesosSuspendidos(archivo, TiempG);

                // 5 Procesos terminados
                AuxiliarBCP = ListaTerminados.RegresaPrimero();
                while (AuxiliarBCP != NULL) {
                    ObjProc = AuxiliarBCP->RegresaInfo();
                    imprimirDatos(ObjProc);
                    cout << left << setw(10) << "Terminado";
                    imprimirTiempos(ObjProc, TiempG);
                    AuxiliarBCP = AuxiliarBCP->RegresaLiga();
                }

                cout << "\nContador global: " << TiempG;
                cout << "\n";

                //Verifica si se preciono C para continuar con la ejecucion
                do{
                    if(kbhit() != 0){
                        char tecla = getch();
                        interrupcion = 0;
                        if(tecla == 'c' || tecla == 'C'){
                            interrupcion = 4;
                        }
                    }
                }while(interrupcion != 4);
                break;
            case 7:
                //Mostrar tabla de paginas
                system("cls");
                cout << "Pausa, pulsa C para continuar\n";
                ImprimirMemoria(Memoria);
                //Verifica si se preciono C para continuar con la ejecucion
                do{
                    if(kbhit() != 0){
                        char tecla = getch();
                        interrupcion = 0;
                        if(tecla == 'c' || tecla == 'C'){
                            interrupcion = 4;
                        }
                    }
                }while(interrupcion != 4);
                break;
            case 8:
                //Suspender
                BanderaSuspendido = true;
                break;
            case 9:
                //Regresar
                BanderaRegresa = true;
                break;
            }
            interrupcion = 0;
        }

        system("cls");

        //Hace una lista auxiliar para porcesos listos
        if (NuevoVacio != true){
            AuxiliarListos = ListaNuevos.RegresaPrimero();
            while (EspaciosLL < 44){
                PObjProc = AuxiliarListos->RegresaApun();
                PObjProc->CambiarTiempoLl(TiempG);
                ObjProc = AuxiliarListos->RegresaInfo();

                if(AsignarPaginas(Memoria, ObjProc)){
                    //Si se asignaron las paginas correctamente
                    ListaListos.InsertaOrdenCrec(ObjProc);
                    EspaciosLL = ObjProc.RegresaPaginas() + EspaciosLL;
                    EspaciosVas = EspaciosVas - ObjProc.RegresaPaginas();
                    ProcR--;
                } else{
                    break; //Salir del ciclo si no se pudieron asignar las paginas
                }

                if (AuxiliarListos->RegresaLiga() == NULL){
                    EspaciosLL = 44; //Para salir del ciclo si ya no hay mas procesos
                    NuevoVacio = true;
                } else {
                    AuxiliarListos = AuxiliarListos->RegresaLiga();
                }

                ListaNuevos.EliminaUnNodo(ObjProc);
            }
            AuxiliarListos = ListaListos.RegresaPrimero();
            AuxiliarEjec = ListaListos.RegresaPrimero();
            if ((44 - EspaciosLL) != EspaciosVas){
                EspaciosLL = EspaciosLL - EspaciosVas;
            }
            if (ListaNuevos.RegresaPrimero() != NULL){
                IdN = ListaNuevos.RegresaPrimero()->RegresaInfo().RegresaID();
                PagN = ListaNuevos.RegresaPrimero()->RegresaInfo().RegresaPaginas();
            } else{
                IdN = 0;
                PagN = 0;
            }
        }

        AuxiliarListos = ListaListos.RegresaPrimero();
        //Recorrer apuntador
        if(AuxiliarListos != NULL){
            if (AuxiliarListos->RegresaLiga() != NULL){
            AuxiliarListos = AuxiliarListos->RegresaLiga(); // ahora apunta al 2o del lote
            } else{
                AuxiliarListos = ListaListos.RegresaPrimero();
            }
            AuxiliarEjec = ListaListos.RegresaPrimero();
        } else{
            AuxiliarEjec = NULL;
        }


        //Verificar si ya se acabaron los procesos
        if (ProcTer == NumProcs) {
                Terminado = true;
        }

        cout << "\nProcesos en cola de Nuevos: " << ProcR;
        if (IdN != 0){
            cout << "\tId del proximo nuevo proceso: " << IdN;
            cout << " Num de paginas del proximo nuevo proceso: " << PagN;
        }

        cout << "\nProcesos Suspendidos: " << ProcS;
        if(ProcS != 0){
            ObjProc = Recuperar(archivo);
            cout << "\tId del proximo proceso a regresar: " << ObjProc.RegresaID();
            cout << " Num de paginas del procimo proceso a regresar: " << ObjProc.RegresaPaginas();
        }

        //Impresion del proceso en ejecucion
        cout << "\nPorceso en ejecucion\n";
        if (Terminado != true && AuxiliarEjec != NULL){
            ObjProc = AuxiliarEjec->RegresaInfo();
            PObjProc = AuxiliarEjec->RegresaApun();
            if (PObjProc->RegresaTiempoQ() <= Quantum){
                if (PObjProc->RegresaTiempoR() == -1){
                    PObjProc->CambiarTiempoR(TiempG - PObjProc->RegresaTiempoLl());
                }
                //Caso por si se ordena un error
                if (BanderaError == true){
                    PObjProc->CambiarError(BanderaError);
                    BanderaError = false;

                    //LiberarPaginas(Memoria, ObjProc.RegresaID());
                }

                if (PObjProc->RegresaTiempoTrans() < PObjProc->RegresaTiempo() && PObjProc->RegresaError() != true){
                    if (PObjProc->RegresaTiempoTrans() != 0){
                        TiempG = TiempG + 1;
                    }

                    //Caso por si se ordena un cambio de proceso
                    if (BanderaBloqueado != true){
                        // Buscar las paginas del proceso en ejecucion para cambiar su estado
                        int ubicacion[PObjProc->RegresaPaginas()][2];
                        BuscarEnMemoria(Memoria, ObjProc.RegresaID(), ubicacion, ObjProc.RegresaPaginas());
                        CambiarEstadoM(Memoria, ubicacion, ObjProc.RegresaPaginas(), 'E');

                        cout << *PObjProc;
                        cout << "\tTamanio: " << PObjProc->RegresaTamanio();
                        cout << "\tTiempo transcurrido: " << PObjProc->RegresaTiempoTrans() << "\n";
                        cout << "Tiempo restante: " << (PObjProc->RegresaTiempo() - PObjProc->RegresaTiempoTrans());
                        cout << "\tTiempo transcurrido del Quantum: " << PObjProc->RegresaTiempoQ();
                        PObjProc->CambiarTiempo(PObjProc->RegresaTiempoTrans() + 1);
                        PObjProc->CambiarTiempoQ(PObjProc->RegresaTiempoQ() + 1);
                        cout << "\n";
                    } else{ //Cambio de contexto a bloqueado
                        ObjSig = AuxiliarEjec->RegresaLiga();
                        ObjProc = AuxiliarEjec->RegresaInfo();

                        // Buscar las paginas del proceso en ejecucion para cambiar su estado
                        int ubicacion[PObjProc->RegresaPaginas()][2];
                        BuscarEnMemoria(Memoria, ObjProc.RegresaID(), ubicacion, ObjProc.RegresaPaginas());
                        CambiarEstadoM(Memoria, ubicacion, ObjProc.RegresaPaginas(), 'B');

                        ListaListos.EliminaUnNodo(ObjProc);
                        ListaBloqueados.InsertaFinal(ObjProc);
                        if(ObjSig != NULL){
                            AuxiliarEjec = ObjSig;
                        } else{
                            AuxiliarEjec = ListaListos.RegresaPrimero();
                        }
                        BanderaBloqueado = false;
                    }
                } else if (PObjProc->RegresaTiempoTrans() == PObjProc->RegresaTiempo() || PObjProc->RegresaError() == true){ //Caso para cuando el proceso a terminado
                    ProcTer++;
                    TiempG = TiempG + 1;
                    EspaciosLL--;
                    EspaciosVas++;
                    PObjProc->CambiarTiempoF(TiempG);
                    ObjSig = AuxiliarEjec->RegresaLiga();
                    ObjProc = AuxiliarEjec->RegresaInfo();

                    EspaciosLL = EspaciosLL - PObjProc->RegresaTamanio();
                    EspaciosVas = EspaciosVas + PObjProc->RegresaTamanio();
                    LiberarPaginas(Memoria, ObjProc.RegresaID());

                    ListaListos.EliminaUnNodo(ObjProc);
                    ListaTerminados.InsertaFinal(ObjProc);
                    if (ObjSig != NULL){
                        AuxiliarEjec = AuxiliarEjec->RegresaLiga();
                    } else {
                        AuxiliarEjec = ListaListos.RegresaPrimero();
                    }
                }
            } else { //Se acabo el quantum
                PObjProc->CambiarTiempoQ(0);
                ObjSig = AuxiliarEjec->RegresaLiga();
                ObjProc = AuxiliarEjec->RegresaInfo();

                // Buscar las paginas del proceso en ejecucion para cambiar su estado
                int ubicacion[PObjProc->RegresaPaginas()][2];
                BuscarEnMemoria(Memoria, ObjProc.RegresaID(), ubicacion, ObjProc.RegresaPaginas());
                CambiarEstadoM(Memoria, ubicacion, ObjProc.RegresaPaginas(), 'L');

                ListaListos.EliminaUnNodo(ObjProc);
                ListaListos.InsertaFinal(ObjProc);
                if(ObjSig != NULL){
                    AuxiliarEjec = ObjSig;
                } else{
                    AuxiliarEjec = ListaListos.RegresaPrimero();
                }
            }
        }

        //Procesos suspendidos
        if(ListaBloqueados.RegresaPrimero() != NULL && BanderaSuspendido != false){
            AuxiliarBloq = ListaBloqueados.RegresaPrimero();
            ObjProc = AuxiliarBloq->RegresaInfo();

            if(ProcS == 0){
                Reiniciar = true;
            } else {
                Reiniciar = false;
            }
            if(Guardar(ObjProc, archivo, Reiniciar)){
                LiberarPaginas(Memoria, ObjProc.RegresaID());
                EspaciosLL = EspaciosLL - ObjProc.RegresaTamanio();
                EspaciosVas = EspaciosVas + ObjProc.RegresaTamanio();
                ListaBloqueados.EliminaUnNodo(ObjProc);
                ProcS++;
            }
            BanderaSuspendido = false;
        }

        //Regresa proceso
        if(BanderaRegresa != false && ProcS != 0){
            ObjProc = Recuperar(archivo);
            if(AsignarPaginas(Memoria, ObjProc)){
                //Si se asignaron las paginas correctamente
                ListaListos.InsertaFinal(ObjProc);
                EspaciosLL = ObjProc.RegresaPaginas() + EspaciosLL;
                EspaciosVas = EspaciosVas - ObjProc.RegresaPaginas();
                ProcS--;
                CopiarMenosPrimero(archivo);
            } else{
                cout << "No hay suficiente espacio en memoria\n";
            }
            BanderaRegresa = false;
        }

        //Procesos bloqueados
        if(ListaBloqueados.RegresaPrimero() != NULL){
            AuxiliarBloq = ListaBloqueados.RegresaPrimero();

            while(AuxiliarBloq != NULL){
                PObjProc = AuxiliarBloq->RegresaApun();
                PObjProc->CambiarTiempoB(PObjProc->RegresaTiempoB() + 1);

                ObjSig = AuxiliarBloq->RegresaLiga();
                if(PObjProc->RegresaTiempoB() > 8){
                    PObjProc->CambiarTiempoB(0);
                    ObjProc = AuxiliarBloq->RegresaInfo();

                    // Buscar las paginas del proceso en ejecucion para cambiar su estado
                    int ubicacion[PObjProc->RegresaPaginas()][2];
                    BuscarEnMemoria(Memoria, ObjProc.RegresaID(), ubicacion, ObjProc.RegresaPaginas());
                    CambiarEstadoM(Memoria, ubicacion, ObjProc.RegresaPaginas(), 'L');

                    ListaBloqueados.EliminaUnNodo(ObjProc);
                    ListaListos.InsertaFinal(ObjProc);
                }
                AuxiliarBloq = ObjSig;
            }
        }

        ImprimirMemoria(Memoria);

        //Procesos terminados
        cout << "\nProcesos terminados: " << ProcTer;
        AuxiliarResul = ListaTerminados.RegresaPrimero();
        for(j = 0; j < ProcTer; j++){
            ObjProc = AuxiliarResul->RegresaInfo();
            cout << "\nID proceso: " << ObjProc.RegresaID();
            cout << "\tOperacion: " << ObjProc.RegresaNumero(1);
            switch(ObjProc.RegresaOperador()){
            case 1:
                cout << " + ";
                ResulProc = ObjProc.RegresaNumero(1) + ObjProc.RegresaNumero(2);
                break;
            case 2:
                cout << " - ";
                ResulProc = ObjProc.RegresaNumero(1) - ObjProc.RegresaNumero(2);
                break;
            case 3:
                cout << " * ";
                ResulProc = ObjProc.RegresaNumero(1) * ObjProc.RegresaNumero(2);
                break;
            case 4:
                cout << " / ";
                ResulProc = ObjProc.RegresaNumero(1) / ObjProc.RegresaNumero(2);
                break;
            case 5:
                cout << " % ";
                ResulProc = ObjProc.RegresaNumero(1) % ObjProc.RegresaNumero(2);
                break;
            case 6:
                cout << " ^ ";
                ResulProc = pow(ObjProc.RegresaNumero(1), ObjProc.RegresaNumero(2));
                break;
            }
            cout << ObjProc.RegresaNumero(2);
            if (ObjProc.RegresaError() != true){
                cout << "\tResultado: " << ResulProc << "\n";
            } else {
                cout << "\tResultado: Error\n";
            }

            if (AuxiliarResul->RegresaLiga() != NULL){
                AuxiliarResul = AuxiliarResul->RegresaLiga();
            }
        }

        cout << "\nContador global: " << TiempG;
        cout << "\n";
        //system("pause");
        sleep(2);

    }while(Terminado == false);
    system("pause");
    //Mostrar tabla BCP
    system("cls");
    cout << "Pausa, pulsa C para continuar\n";
    cout << left << setw(4)  << "ID"
            << setw(11) << "Operacion"
            << setw(10) << "Resultado"
            << setw(10) << "Estado"
            << setw(16) << "T Llegada"
            << setw(16) << "T Finalizacion"
            << setw(16) << "T Retorno"
            << setw(16) << "T Respuesta"
            << setw(16) << "T Espera"
            << setw(16) << "T Servicio"
            << "\n";

    // Procesos terminados
    AuxiliarBCP = ListaTerminados.RegresaPrimero();
    while (AuxiliarBCP != NULL) {
        ObjProc = AuxiliarBCP->RegresaInfo();
        imprimirDatos(ObjProc);
        cout << left << setw(10) << "Terminado";
        imprimirTiempos(ObjProc, TiempG);
        AuxiliarBCP = AuxiliarBCP->RegresaLiga();
    }

    cout << "\nContador global: " << TiempG;
    cout << "\n";
}
