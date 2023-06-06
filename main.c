#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "Map.h"
#include "cartas.h"

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
    char *cartas[3];
} jugadorPiramide;

void tomanji(Map *jugadores)
{

}

void piramide(Map *jugadores)
{

    Baraja baraja1;
    Baraja baraja2;

    inicializarBaraja(baraja1);
    inicializarBaraja(baraja2);

    barajar(baraja1);
    barajar(baraja2);

    //Stack *pila1 = stack_create();
    //Stack *pila2 = stack_create();

    printf("\e[1;1H\e[2J");
    printf(LINEA);
    printf("|   Bienvenido a piramide.        |\n");
    printf(LINEA);
    printf("Cuantos jugadores van a jugar?\n");
    int cantidadJugadores = 0;
    scanf("%d", &cantidadJugadores);
    getchar();

    int k = 0;

    for (int i = 0; i < cantidadJugadores; i++)
    {
        jugadorPiramide *jugador= (jugadorPiramide *)malloc(sizeof(jugadorPiramide));

        if (jugador == NULL)
        {
            printf("No se pudo asignar memoria.\n");
            exit(0);
        }

        char nombre[21];
        printf("Ingrese nombre del jugador %d: ", i + 1);
        scanf("%20s", nombre); 
        getchar();
        jugador->nombre = nombre;
        printf("a");

        jugador->puntos = 0;
        for (int j = 0; j < 3; j++)
        {
            jugador->cartas[j] = malloc(sizeof(char) * 20);
            
            if (jugador->cartas[j] == NULL)
            {
                printf("No se pudo asignar memoria.\n");
                exit(0);
            }

            strcpy(jugador->cartas[j], baraja1[k].numero);
            strcat(jugador->cartas[j], "de");
            strcat(jugador->cartas[j],baraja1[k].palo);
            k++;
        }

        insertMap(jugadores, jugador->nombre, jugador);

    }

    for (int i = 1; i <= 7; i++) 
    {
       for (int j = 1; j <= 7 - i; j++) 
       {
           printf(" ");
       }
       for (int k = 1; k <= 2 * i - 1; k++) 
       {
           if (i == 1) printf("**");
           else
               printf("*");
       }
       printf("\n");
    }
    

    printf("\n");
    printf("Entregando cartas...");

}

int main()
{   
    Map *jugadores = createMap(is_equal_string);
    int opcion;
    printf(LINEA);
    printf("|           Bienvenidos!         |\n");
    printf(LINEA);
    printf("Que deseas jugar?\n");
    printf("1. Tomanji\n");
    printf("2. Piramide\n");
    printf("0. Salir\n");

    scanf("%d", &opcion);

    switch (opcion)
    {
        case 1:
            for (int i = 0; i < 1; i++)
            {
                printf("\e[1;1H\e[2J");
                printf("Entrando a tomanji.\n");
                sleep(1);
                printf("\e[1;1H\e[2J");
                printf("Entrando a tomanji..\n");
                sleep(1);
                printf("\e[1;1H\e[2J");
                printf("Entrando a tomanji...\n");
                sleep(1);
            }
            tomanji(jugadores);
            break;
        case 2:
            for (int i = 0; i < 1; i++)
            {
                printf("\e[1;1H\e[2J");
                printf("Entrando a piramide.\n");
                sleep(1);
                printf("\e[1;1H\e[2J");
                printf("Entrando a piramide..\n");
                sleep(1);
                printf("\e[1;1H\e[2J");
                printf("Entrando a piramide...\n");
                sleep(1);
            }
            piramide(jugadores);
            break;
    }

    return 0;
}