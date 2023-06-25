#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include "Map.h"
#include "cartas.h"
#include "menu.h"
#include "gotoxy.h"

#define LINEA "----------------------------------\n"

const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ';'){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ';'){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

int is_equal_string(void *key1, void *key2)
{
    if (strcmp((char *)key1, (char *)key2) == 0)
    {
        return 1;
    }
    return 0;
}

typedef struct
{
    char nombre[20];
    int puntos;
    Carta *cartas[3];
} jugadorPiramide;

typedef struct {
    char nombreTomanji[20];
    int cantSorbos;
} jugadorTomanji;

typedef struct {
    char tituloTomanji[1000];
    char retoTomanji[1000];
    int tragos;
    bool repetido;
} retoTomanji;

void mostrarJugadoresTomaji(Map *jugadores, int cantidadJugadores)
{
    printf("\n\n");
    printf(LINEA);
    printf("\n");

    jugadorTomanji *jugador = firstMap(jugadores);
    {
        for (int i =0 ; i < cantidadJugadores; i++)
        {
            printf("Jugador: %s\n", jugador->nombreTomanji);
            printf("Sorbos: %d\n", jugador->cantSorbos);
            
            printf("\n\n");
            printf(LINEA);
            printf("\n");

            jugador = nextMap(jugadores);
        }
    }
}

List *importarRetosTomanji()
{
    retoTomanji retos;
    List *listaRetos = createList();
    FILE *fp = fopen ("retos.csv", "r");

    if (!fp)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
        return NULL;
    }

    char linea[1024];
    int i;
    int tragos;

    fgets(linea, 1023, fp);
    int k=0;
    while (fgets (linea, 1023, fp) != NULL) 
    {
        for(i=0; i<3; i++){
            const char *aux = get_csv_field(linea, i); 
            
            switch(i)
            {
                case 0: 
                    //printf("TITULO: %s", aux);
                    strcpy(retos.tituloTomanji, aux);
                    break;
                case 1: 
                    //printf("RETO: %s", aux);
                    strcpy(retos.retoTomanji, aux);
                    break;
                case 2: 
                    //printf("TRAGOS: %s", aux);
                    tragos = (int) strtol(aux, NULL, 10);
                    retos.tragos = tragos;
                    break;
            }
            printf("\n");
        }

        retos.repetido = false;
        int random = rand() % 50;
        if (random % 2 == 0)
        {
            pushFront(listaRetos, retos);
        }
        else
        {
            pushBack(listaRetos, retos);
        }
        printf("\n");
        k++; if(k==50) break;
    }

    /*for(k = 0 ; k < 49 ; k++)
    {
        printf("%s\n", arregloDeRetos[k].tituloTomanji);
        printf("%s\n", arregloDeRetos[k].retoTomanji);
        printf("%d\n", arregloDeRetos[k].tragos);
        printf("\n");
    }*/
    printf("Se importaron los retos\n");
    fclose(fp);
    sleep(2);
    SortLinkedList(listaRetos);
    return listaRetos;
}

void tomanjiRetos(List *retos, Map *jugadores, int cantidadJugadores)
{
    bool game = true;
    int cont = 0;
    retoTomanji *reto = firstList(retos);
    while (game == true)
    {
        if (cont == 50)
        {
            printf("Se acabaron los retos\n");
            return;
        }

        if (reto->repetido == 1)
        {
            reto = nextList(retos);
            continue;
        }
        if (cont % 15)
        {
            printf("Desean Continuar? (S/N)\n");
            char respuesta;
            scanf("%c", &respuesta);
            getchar();
            if (respuesta == 'N' || respuesta == 'n')
            {
                return;
            }

        }

        system("cls");
        printf(LINEA);
        system("color 04");
        gotoxy(10, 10); ("Titulo: %s\n", reto->tituloTomanji);
        printf("\n");
        system("color");
        gotoxy(10, 11); ("Reto: %s\n", reto->retoTomanji);
        printf("Tragos: %d\n", reto->tragos);
        reto->repetido = true;
        
        printf("Presione enter para continuar.\n");
        system("pause >nul");
        system("cls");
        
        reto = nextList(retos);
    }
}

void tomanji(Map *jugadores)
{
    system("cls");
    printf(LINEA);
    printf("|   Bienvenido a Tomaji.        |\n");
    printf(LINEA);
    printf("Cuantos jugadores van a jugar?\n");
    int cantidadJugadores = 0;
    scanf("%d", &cantidadJugadores);
    getchar();
    if (cantidadJugadores < 0 || cantidadJugadores > 15)
    {
        printf("Cantidad de jugadores invalida.\n");
        exit(0);
    }

    for (int i = 0; i < cantidadJugadores; i++)
    {
        jugadorTomanji *jugador= (jugadorTomanji *)malloc(sizeof(jugadorTomanji));

        if (jugador == NULL)
        {
            printf("No se pudo asignar memoria.\n");
            exit(1);
        }

        char nombre[20];
        printf("Ingrese nombre del jugador %d: ", i + 1);
        scanf("%s", nombre); 
        strcpy(jugador->nombreTomanji, nombre);

        jugador->cantSorbos = 0;
        
        insertMap(jugadores, jugador->nombreTomanji, jugador);

    }

    mostrarJugadoresTomaji(jugadores, cantidadJugadores);
    fflush(stdin);
    printf("Presione ENTER para comenzar el juego!!\n");
    system("pause >nul");
    List *retos = importarRetosTomanji();
    system("cls");
    tomanjiRetos(retos, jugadores, cantidadJugadores);
}

void mostrarJugadores(Map *jugadores, int cantidadJugadores)
{
    jugadorPiramide *jugador = firstMap(jugadores);
    {
        for (int i = 0; i < cantidadJugadores; i++)
        {
            printf("Jugador: %s\n", jugador->nombre);
            printf("Puntos: %d\n", jugador->puntos);
            printf("Cartas: ");
            for (int j = 0; j < 3; j++)
            {
                switch (jugador->cartas[j]->numero)
                {
                case 1:
                    printf("A");
                    break;
                case 11:
                    printf("J");
                    break;
                case 12:
                    printf("Q");
                    break;
                case 13:
                    printf("K");
                    break;

                default:
                    printf("%d", jugador->cartas[j]->numero);
                    break;
                }

                if (j != 2)
                {
                    printf(" - ");
                }

            }
            printf("\n\n");
            printf(LINEA);
            printf("\n");

            jugador = nextMap(jugadores);
        }
    }
}

void mostrarPiramide()
{
    int base = 1;
    int altura = 7;

    system("cls");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.dwSize.X;

    int i, j;
    for (i = 0; i < altura; i++) 
    {
        int espacios = (consoleWidth - base) / 2;
        gotoxy(espacios, i + 1);
        for (j = 0; j < base; j++) 
        {
            printf("*");
        }
        base += 2;
    }

    gotoxy(0, altura + 2);

}

void juegoPiramide(Map *jugadores, int cantidadJugadores, Stack *pila)
{
    Carta *carta[48];
    Carta *cartaAux[48] = {NULL};
    int ultimaCarta = 48;

    for (int i = 0; i < 48; i++)
    {
        carta[i] = stack_pop(pila);
    }

    system("cls");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int i, j;
    bool game = true;
    int numerosImpresos = 0;

    while (game)
    {
        int base = 1;
        int pos = 0;
        bool flag = false;
        int altura = 7;

        system("cls");

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int consoleWidth = csbi.dwSize.X;
        
        int i, j;
        int cont = 0;
        int numero = 0;

        for (i = 0; i < altura; i++) 
        {
            int espacios = (consoleWidth - base) / 2;
            
            gotoxy(espacios, i + 1);
            if (i > 1)
                gotoxy(espacios, i + 1);
            for (j = 0; j < base; j++) 
            {
                if (cont >= ultimaCarta)
                {
                    switch (carta[numero]->numero)
                    {
                        case 1:
                            printf(" A");
                            pos++;
                            break;
                        case 11:
                            printf(" J");
                            pos++;
                            break;
                        case 12:
                            printf(" Q");
                            pos++;
                            break;
                        case 13:
                            printf(" K");
                            pos++;
                            break;
                        default:
                            printf(" %d", carta[numero]->numero);
                            pos++;
                            break;
                    }
                    flag = true;

                    cartaAux[numerosImpresos] = carta[numero];
                    
                    if (numerosImpresos >= 0)
                    {
                        for (int k = numerosImpresos - 1; k >= 0; k--)
                        {   

                            switch (cartaAux[k]->numero)
                            {
                                case 1:
                                    printf(" A");
                                    pos++;
                                    break;
                                case 11:
                                    printf(" J");
                                    pos++;
                                    break;
                                case 12:
                                    printf(" Q");
                                    pos++;
                                    break;
                                case 13:
                                    printf(" K");
                                    pos++;
                                    break;
                                case 14: 
                                    printf(" A");
                                    pos++;
                                    break;
                                default:
                                    printf(" %d", cartaAux[k]->numero);
                                    pos++;
                                    break;
                            }
                            if (pos % 13 == 0)
                            {
                                printf("\n");
                                gotoxy(espacios, i + 1);
                            }
                        }
                    }
                    
                    numerosImpresos++;

                    if (numero < ultimaCarta)
                    {
                        ultimaCarta--;
                        cont = 0;
                    }
                    numero++;
                }
                else if (flag == false)
                {
                    printf("*");
                    pos++;
                    cont++;
                }
                numero = ultimaCarta - 1;
            }
            base += 2;
        }

        gotoxy(0, altura + 2);

        fflush(stdin);
        printf("\n\n");
        printf("Presione enter para continuar.\n");
        system("pause >nul");

        system("cls");

        if (ultimaCarta == 0)
        {
            game = false;
        }

    }

    gotoxy(0, csbi.dwCursorPosition.Y + 2);
    Sleep(3000);
}


void piramide(Map *jugadores)
{

    Stack *pila1 = stack_create();
    Stack *pila2 = stack_create(); 
    
    crearPila(pila1);
    crearPila(pila2);

    system("cls");
    printf(LINEA);
    printf("|   Bienvenido a piramide.        |\n");
    printf(LINEA);
    printf("Cuantos jugadores van a jugar?\n");
    int cantidadJugadores = 0;
    scanf("%d", &cantidadJugadores);
    getchar();
    if (cantidadJugadores < 0 || cantidadJugadores > 15)
    {
        printf("Cantidad de jugadores invalida.\n");
        exit(0);
    }

    for (int i = 0; i < cantidadJugadores; i++)
    {
        jugadorPiramide *jugador= (jugadorPiramide *)malloc(sizeof(jugadorPiramide));

        if (jugador == NULL)
        {
            printf("No se pudo asignar memoria.\n");
            exit(0);
        }

        char nombre[20];
        printf("Ingrese nombre del jugador %d: ", i + 1);
        scanf("%s", nombre); 
        strcpy(jugador->nombre, nombre);

        jugador->puntos = 0;
        for (int j = 0; j < 3; j++)
        {
            jugador->cartas[j] = malloc(sizeof(char) * 20);
            
            if (jugador->cartas[j] == NULL)
            {
                printf("No se pudo asignar memoria.\n");
                exit(0);
            }
            jugador->cartas[j] = stack_pop(pila1);
        }

        printf("Entregando cartas...\n");
        sleep(1);
        insertMap(jugadores, jugador->nombre, jugador);

    }

    system("cls");
    mostrarPiramide();

    printf("\n");
    printf(LINEA);

    mostrarJugadores(jugadores, cantidadJugadores);
    fflush(stdin);
    printf("Presione enter para continuar.\n");
    system("pause >nul");

    printf(LINEA);
    printf("Revelando primera carta:\n");
    sleep(1);
    system("cls");
    juegoPiramide(jugadores, cantidadJugadores, pila2);
}

int main()
{   
    Map *jugadores = createMap(is_equal_string);
    
    GetAllKeys();
    ocultarCursor();

    int opcion = menu();

    switch (opcion)
    {
        case 1:
            tomanji(jugadores);
            break;
        case 2:
            piramide(jugadores);
            break;
    }
        


    return 0;
}
