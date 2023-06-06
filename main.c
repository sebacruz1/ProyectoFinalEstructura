#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "Map.h"

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
    int cantidad;
    int cartas[3];
} jugadorPiramide;

void tomanji(Map *jugadores)
{

}

void piramide(Map *jugadores)
{
    printf("\e[1;1H\e[2J");
    printf(LINEA);
    printf("|   Bienvenido a piramide.        |\n");
    printf(LINEA);
    printf("Cuantos jugadores van a jugar?\n");
    int cantidadJugadores;
    scanf("%d", &cantidadJugadores);



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