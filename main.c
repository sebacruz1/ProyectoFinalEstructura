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

const char *get_csv_field(char *tmp, int k) {
    int open_mark = 0;
    int ini_i = 0, i = 0;
    int j = 0;
    int tmp_len = strlen(tmp);
    char *ret = (char *)malloc((tmp_len + 1) * sizeof(char));

    while (tmp[i + 1] != '\0') {
        if (tmp[i] == '\"') {
            open_mark = 1 - open_mark;
            if (open_mark) {
                ini_i = i + 1;
            }
            i++;
            continue;
        }

        if (open_mark || tmp[i] != ';') {
            if (k == j) {
                ret[i - ini_i] = tmp[i];
            }
            i++;
            continue;
        }

        if (tmp[i] == ';') {
            if (k == j) {
                ret[i - ini_i] = 0;
                return ret;
            }
            j++;
            ini_i = i + 1;
        }

        i++;
    }

    if (k == j) {
        ret[i - ini_i] = 0;
        return ret;
    }

    free(ret);
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
    retoTomanji retos;

    while (fgets (linea, 1023, fp) != NULL) 
    {
        retoTomanji *temp = (retoTomanji *)malloc(sizeof(retoTomanji));
        for(i=0; i<3; i++)
        {
            const char *aux = get_csv_field(linea, i); 
            switch(i)
            {
                case 0: 
                    strcpy(temp->tituloTomanji, aux);
                    break;
                case 1: 
                    strcpy(temp->retoTomanji, aux);
                    break;
                case 2: 
                    tragos = (int) strtol(aux, NULL, 10);
                    temp->tragos = tragos;
                    break;
                default: 
                    printf("ERROR\n");
                    break;
            }
            printf("\n");
        }
        retoTomanji *newRetos = (retoTomanji *)malloc(sizeof(retoTomanji));
        if (newRetos == NULL) {
            printf("Memory allocation error\n");
            break;
        }

        // Copy the data from retos to newRetos
        strcpy(newRetos->tituloTomanji, temp->tituloTomanji);
        strcpy(newRetos->retoTomanji, temp->retoTomanji);
        newRetos->tragos = temp->tragos;

        int random = rand() % 50;
        if (random % 2 == 0) {
            pushFront(listaRetos, newRetos);
        } else {
            pushBack(listaRetos, newRetos);
        }
        printf("\n");
        k++;
        if (k == 50) break;
    }

    fclose(fp);
    SortLinkedList(listaRetos);
    return listaRetos;
}

void tomanjiRetos(List *retos, Map *jugadores, int cantidadJugadores)
{
    bool game = true;
    jugadorTomanji *jugador = firstMap(jugadores);
    int cont = 0;
    retoTomanji *reto = firstList(retos);
    printf("Comenzando el juego...\n");
    sleep(2);
    system("cls");
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
        if (cont % 15 == 0 && cont != 0)
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

        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        system("cls");

        setConsoleColor(FOREGROUND_YELLOW);
        gotoxy(10, 2); printf("Jugador: %s\n", jugador->nombreTomanji);
        gotoxy(10,3); printf("Puntos (Cantidad Tomada): %d\n", jugador->cantSorbos);
        gotoxy(10,4); printf(LINEA);
        setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        gotoxy(10, 5); 
        printf("|Titulo: %s\n", reto->tituloTomanji);
        printf("\n");
        setConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        gotoxy(10, 6); 
        printf("|Reto: %s\n", reto->retoTomanji);
        setConsoleColor(FOREGROUND_CYAN);
        gotoxy(10, 7); printf("|Puntos: %d\n", reto->tragos);	
        setConsoleColor(FOREGROUND_YELLOW);
        gotoxy(10, 8);printf(LINEA);
        printf("\n");
        reto->repetido = true;

        setConsoleColor(FOREGROUND_DARK_BLUE);

        gotoxy(10, 10); 
        printf("El jugador logro el reto?\n");
        printf("1. Si\n");
        printf("2. No\n");
        printf("0. Salir\n");

        int respuesta;
        scanf("%d", &respuesta);
        getchar();

        if (respuesta == 1)
        {
            jugador->cantSorbos += reto->tragos;
        }
        else if (respuesta == 0)
        {
            return;
        }

        printf("Presione ENTER para continuar.\n");
        system("pause >nul");
        system("cls");

        reto = nextList(retos);
        jugador = nextMap(jugadores);
        if (jugador == NULL)
        {
            jugador = firstMap(jugadores);
        }
    }
}

void finalizarJuego(Map *jugadores, int cantidadJugadores)
{
    mostrarJugadoresTomaji(jugadores, cantidadJugadores);

    system("cls");
    jugadorTomanji *jugador = firstMap(jugadores);
    char ganador[20] = "\0";

    printf("El ganador es ...");
    for (int i = 0; i < cantidadJugadores; i++)
    {
        int max = 0;
        if (jugador->cantSorbos > max)
        {
            max = jugador->cantSorbos;
            strcpy(ganador, jugador->nombreTomanji);
        }
        jugador = nextMap(jugadores);

    }

    if (strcmp(ganador, "\0") == 0)
    {
        gotoxy(10,10);
        printf("No hay ganador. :C \n");
        gotoxy(10,11);
        printf("Presione ENTER para finalizar.\n");
        system("pause >nul");
        system("cls");
        printf("Gracias por jugar.\n");	
        sleep(3);
        exit(0);
        
    }

    gotoxy(10,9); 
    printf(LINEA);
    gotoxy(10,10);
    printf("!!%s!!", ganador);
    gotoxy(10,11);
    printf(LINEA);
    printf("Presione ENTER para continuar.\n");
    system("pause >nul");
    system("cls");
    exit(0); 
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
    finalizarJuego(jugadores, cantidadJugadores);
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

void mostrarJugadoresCartas(Map *jugadores, int cantidadJugadores, int carta)
{
    printf("\n\n");
    jugadorPiramide *jugador = firstMap(jugadores);
    
    printf("Jugadores que beben: \n");
    for (int i = 0; i < cantidadJugadores; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (jugador->cartas[j]->numero == carta)
            {
                printf("%s\n", jugador->nombre);
                jugador->puntos++;
                printf("Cartas: ");
                for (int k = 0; k < 3; k++)
                {
                    switch (jugador->cartas[k]->numero)
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
                            printf("%d", jugador->cartas[k]->numero);
                            break;
                    }

                    if (k != 2)
                    {
                        printf(" - ");
                    }
                }
                printf("\n\n");
                printf(LINEA);
                printf("\n");
                break;
            }

        }
        jugador = nextMap(jugadores);
    }
}

void juegoPiramide(Map *jugadores, int cantidadJugadores, Stack *pila)
{
    Carta *carta[48];
    Carta *cartaAux[48] = {NULL};
    int ultimaCarta = 48;
    int nuevaCarta = 0;
    int posNuevaCarta = 0;

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
        posNuevaCarta++;
        for (i = 0; i < altura; i++) 
        {
            int espacios = (consoleWidth - base) / 2;
            int yAxis = i;
            gotoxy(espacios, i);
            
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
                    
                    nuevaCarta = cartaAux[numerosImpresos]->numero;                    
                    
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

        mostrarJugadoresCartas(jugadores, cantidadJugadores, nuevaCarta);

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
