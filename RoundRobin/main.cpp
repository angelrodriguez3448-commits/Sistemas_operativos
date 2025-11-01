#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include "Lista.h"
#include "Proceso.h"
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
    if(ObjProc.RegresaID() == 1){
        cout << left << setw(16) << "0";
    } else if(ObjProc.RegresaTiempoLl() < 0){
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

int main(){
    cout << "--Simulador de algoritmo de planificacion Round-Robin--\n\n";
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
    int Oper, Num1, Num2, Tiemp, Id;
    Id = 0;
    int NumProcs, i, j, interrupcion, EspaciosLL, EspaciosVas, ProcTer, ProcR, TiempG, NivelBCP, TiempP, Quantum;
    float ResulProc;
    srand(time(NULL));
    bool BanderaError = false;
    bool BanderaBloqueado = false;
    bool Terminado = false;

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
        Proceso ObjProc(Oper, Num1, Num2, Tiemp, Id);
        ListaNuevos.InsertaOrdenCrec(ObjProc);
    }

    AuxiliarListos = ListaNuevos.RegresaPrimero();
    ProcR = NumProcs;
    ProcTer = 0;
    TiempG = 0;
    TiempP = 0;
    EspaciosLL = 0;
    EspaciosVas = 4;


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
                Proceso ObjProc(Oper, Num1, Num2, Tiemp, Id);
                ListaNuevos.InsertaOrdenCrec(ObjProc);
                break;
            }
            case 6:
                //Mostrar tabla BCP
                system("cls");
                 NivelBCP = 0;
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

                // 4 Procesos terminados
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
            }
            interrupcion = 0;
        }

        system("cls");

        //Hace una lista auxiliar para porcesos listos
        if (ListaNuevos.RegresaPrimero() != NULL){
            AuxiliarListos = ListaNuevos.RegresaPrimero();
            while (EspaciosLL < 4 ){
                PObjProc = AuxiliarListos->RegresaApun();
                PObjProc->CambiarTiempoLl(TiempG);
                ObjProc = AuxiliarListos->RegresaInfo();
                ListaListos.InsertaOrdenCrec(ObjProc);
                EspaciosLL++;
                EspaciosVas--;
                if (AuxiliarListos->RegresaLiga() == NULL){
                    EspaciosLL = 4;
                } else {
                    AuxiliarListos = AuxiliarListos->RegresaLiga();
                }
                ListaNuevos.EliminaUnNodo(ObjProc);
                ProcR--;
            }
            AuxiliarListos = ListaListos.RegresaPrimero();
            AuxiliarEjec = ListaListos.RegresaPrimero();
            if ((4 - EspaciosLL) != EspaciosVas){
                EspaciosLL = EspaciosLL - EspaciosVas;
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
        //Procesos Listos
        cout << "\nCola de listos\n";
        while(AuxiliarListos != NULL && AuxiliarEjec->RegresaLiga() != NULL){
            ObjProc = AuxiliarListos->RegresaInfo();
            cout << "\nID: " << ObjProc.RegresaID();
            cout << "\tTME: " << ObjProc.RegresaTiempo();
            cout << "\tT Transcurrido: " << ObjProc.RegresaTiempoTrans();
            AuxiliarListos = AuxiliarListos->RegresaLiga();
        };

        //Impresion del proceso en ejecucion
        cout << "\n\nPorceso en ejecucion\n";
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
                    //PObjProc->CambiarTiempo(PObjProc->RegresaTiempo());
                }

                if (PObjProc->RegresaTiempoTrans() < PObjProc->RegresaTiempo() && PObjProc->RegresaError() != true){
                    if (PObjProc->RegresaTiempoTrans() != 0){
                        TiempG = TiempG + 1;
                    }

                    //Caso por si se ordena un cambio de proceso
                    if (BanderaBloqueado != true){
                        cout << *PObjProc;
                        cout << "\tTiempo transcurrido: " << PObjProc->RegresaTiempoTrans() << "\n";
                        cout << "Tiempo restante: " << (PObjProc->RegresaTiempo() - PObjProc->RegresaTiempoTrans());
                        cout << "\tTiempo transcurrido del Quantum: " << PObjProc->RegresaTiempoQ();
                        PObjProc->CambiarTiempo(PObjProc->RegresaTiempoTrans() + 1);
                        PObjProc->CambiarTiempoQ(PObjProc->RegresaTiempoQ() + 1);
                        cout << "\n";
                    } else{ //Cambio de contexto a bloqueado
                        ObjSig = AuxiliarEjec->RegresaLiga();
                        ObjProc = AuxiliarEjec->RegresaInfo();
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
                    ListaListos.EliminaUnNodo(ObjProc);
                    ListaTerminados.InsertaFinal(ObjProc);
                    if (ObjSig != NULL){
                        AuxiliarEjec = AuxiliarEjec->RegresaLiga();
                    } else {
                        AuxiliarEjec = ListaListos.RegresaPrimero();
                    }
                }
            } else {
                PObjProc->CambiarTiempoQ(0);
                ObjSig = AuxiliarEjec->RegresaLiga();
                ObjProc = AuxiliarEjec->RegresaInfo();
                ListaListos.EliminaUnNodo(ObjProc);
                ListaListos.InsertaFinal(ObjProc);
                if(ObjSig != NULL){
                    AuxiliarEjec = ObjSig;
                } else{
                    AuxiliarEjec = ListaListos.RegresaPrimero();
                }
            }
        }

        //Procesos bloqueados
        cout << "\nProcesos bloqueados\n";
        if(ListaBloqueados.RegresaPrimero() != NULL){
            AuxiliarBloq = ListaBloqueados.RegresaPrimero();

            while(AuxiliarBloq != NULL){
                PObjProc = AuxiliarBloq->RegresaApun();
                cout << "ID: " << PObjProc->RegresaID() << "\t";
                cout << "Tiempo Bloqueado: " << PObjProc->RegresaTiempoB() << "\n";
                PObjProc->CambiarTiempoB(PObjProc->RegresaTiempoB() + 1);

                ObjSig = AuxiliarBloq->RegresaLiga();
                if(PObjProc->RegresaTiempoB() > 8){
                    PObjProc->CambiarTiempoB(0);
                    ObjProc = AuxiliarBloq->RegresaInfo();
                    ListaBloqueados.EliminaUnNodo(ObjProc);
                    ListaListos.InsertaFinal(ObjProc);
                }
                AuxiliarBloq = ObjSig;
            }
        }

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
        sleep(1);

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
