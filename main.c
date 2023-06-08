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
            
            printf("\n\n");
            printf(LINEA);
            printf("\n");

            jugador = nextMap(jugadores);
        }
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
            exit(0);
        }

        char nombre[20];
        printf("Ingrese nombre del jugador %d: ", i + 1);
        scanf("%s", nombre); 
        strcpy(jugador->nombreTomanji, nombre);

        jugador->cantSorbos = 0;
        
        sleep(1);
        insertMap(jugadores, jugador->nombreTomanji, jugador);

    }

    mostrarJugadoresTomaji(jugadores, cantidadJugadores);
    fflush(stdin);
    printf("Presione ENTER para comenzar el juego!!\n");
    getchar();

}

void gotoxy(int x, int y) 
{
    printf("\033[%d;%df", y, x);
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
    int base = 7; 
    int espacios, i, j, k;
    int pantalla_ancho = 80;

    espacios = (pantalla_ancho - 7) / 2;

    for (i = 1; i <= base; i += 2) 
    {
        for (j = 0; j < espacios; j++) 
        {
            printf(" ");
        }

        for (k = 0; k < i; k++) 
        {
            printf("*");
        }

        printf("\n");
        espacios--;
    }
}

void juegoPiramide(Map *jugadores, int cantidadJugadores, Stack *pila)
{
    Carta *carta[30];
        
    int ultimaCarta = 29;

    
    for (int i = 0; i < 30; i++)
    {
        carta[i] = malloc(sizeof(Carta));
        carta[i] = stack_pop(pila);
    }
    
    int base = 7; 
    int espacios, i, j, k;
    int pantalla_ancho = 80;

    espacios = (pantalla_ancho - 7) / 2;

    for (i = 1; i <= base; i += 2) 
    {
        for (j = 0; j < espacios; j++) 
        {
            printf(" ");
        }

        for (k = 0; k < i; k++) 
        {
            printf("*");
        }

        printf("\n");
        espacios--;
    }
    sleep(3);
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
    getchar();

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
