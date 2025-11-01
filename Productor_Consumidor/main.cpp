#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <unistd.h>

using namespace std;

void imprimirBuffer(int buffer[]){
    for (int i=0; i<18; i++){
        if (buffer[i] == 1){
            cout << "\033[32m"  << "1" << "\033[0m" << " - "; //Imprime los 1 de color verde
        } else {
            cout << "\033[31m"  << "0" << "\033[0m" << " - "; //Imprime los 0 de color rojo
        }

    }
}

int main()
{
    int LineaProduccion [18];
    int productor;
    int consumidor;
    srand(time(NULL));
    int i;
    char tecla;
    bool finalizar = false;
    int indiceP, indiceC; //indice para cada sujeto el cual indica el ultimo acceso
    int control, accion, contador; //control para indicar quien tiene el control de la linea 0 para productor y 1 para consumidor
                                                  //accion para indicar cuantos productos seran producidos o consumidos
                                                  //contador para llevar la cuenta de cuantos productos hay en la linea

    indiceP = indiceC = accion = contador = 0;

    cout << "Programa Productor/Consumidor\n";

    //Inicializador del arreglo con cero, la linea de produccion esta vacia
    for (i=0; i<18; i++){
            LineaProduccion[i] = 0;
    }
    imprimirBuffer(LineaProduccion);
    cout << "\n";
    sleep(1);
    system("cls");

    do {

        //Comprobacion de la tecla de escape
        if(kbhit() != 0){
            tecla = getch();
            if ((int)tecla == 27){
                finalizar = true;
            }
        }

        //Generacion de los puntajes
        productor = rand() % 101;
        consumidor = rand() % 101;

        //Se le concede el turno al sujeto con mayor puntaje
        if (productor > consumidor){
            control = 0;
        } else {
            control = 1;
        }

        //Generacion de la cantidad de la accion a realizar
        do{
            accion = rand() %  7;
        } while (accion < 3);

        //Switch para seleccionar el caso segun el sujeto en control
        switch(control){
        case 0://Caso para productor

            //Condicion para que el productor pueda producir
            if (18 - contador >= accion){
                for (i = 0; i<accion; i++){
                    cout << "Productor despierto\tProduciendo " << accion;
                    cout << "\n";
                    if (indiceP > 17){
                        indiceP = 0;
                    }
                    LineaProduccion[indiceP] = 1;
                    indiceP++;
                    contador++;

                    imprimirBuffer(LineaProduccion);

                    sleep(1);
                    system("cls");
                }
            } else {
                cout << "Productor despierto\tProduciendo " << accion;
                cout << "\n";
                cout << "Accion no realizable\n";
                imprimirBuffer(LineaProduccion);
            }
            break;
        case 1://Caso para el consumidor

            //Condicion para que el consumidor pueda consumir
            if (contador >= accion){
                for (i = 0; i<accion; i++){
                    cout << "Consumidor despierto\tConsumiendo " << accion;
                    cout << "\n";
                    if (indiceC > 17){
                        indiceC = 0;
                    }
                    LineaProduccion[indiceC] = 0;
                    indiceC++;
                    contador--;

                    imprimirBuffer(LineaProduccion);

                    sleep(1);
                    system("cls");
                }
            } else {
                cout << "Consumidor despierto\tConsumiendo " << accion;
                cout << "\n";
                cout << "Accion no realizable\n";
                imprimirBuffer(LineaProduccion);
            }
            break;
        }

        sleep(1);
        system("cls");
    } while (finalizar != true);
}
