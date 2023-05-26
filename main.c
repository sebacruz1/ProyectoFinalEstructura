#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define LINEA "----------------------------------\n"


typedef struct
{
    char nombre[20];
    int cantidad;
} jugadorPiramide;

void tomanji()
{

}

void piramide()
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

}

int main()
{   int opcion;
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
            tomanji();
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
            piramide();
            break;
    }

    return 0;
}