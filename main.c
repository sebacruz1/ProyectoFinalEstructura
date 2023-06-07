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
    Carta *cartas[3];
} jugadorPiramide;

void tomanji(Map *jugadores)
{

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
                    printf("A de");
                    break;
                case 11:
                    printf("J de");
                    break;
                case 12:
                    printf("Q de");
                    break;
                case 13:
                    printf("K de");
                    break;

                default:
                    printf("%d de", jugador->cartas[j]->numero);
                    break;
                }


                switch (jugador->cartas[j]->palo)
                {
                case Pica:
                    printf(" Picas ");
                    break;
                case Corazon:
                    printf(" Corazones");
                    break;
                case Diamante:
                    printf(" Diamantes");
                    break;
                case Trebol:
                    printf(" Treboles");
                    break;
                default:
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
    for (int i = 0; i < 7; i++) 
    {

        for (int j = 0; j < 7 - i - 1; j++) 
        {
            printf(" ");
        }
        
        if (i == 0) 
        {
            printf("* \n");
            for (int j = 0; j < 7 - i - 1; j++) 
            {
                printf(" ");
            }
        }

        for (int k = 0; k < i + 1; k++) 
        {
            printf("* ");
        }
        
        printf("\n");
    }
    
    printf("\n");
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
    
    for (int i = 0; i < 7; i++) 
    {

        for (int j = 0; j < 7 - i - 1; j++) 
        {
            printf(" ");
        }
        
        if (i == 0) 
        {
            printf("* \n");
            for (int j = 0; j < 7 - i - 1; j++) 
            {
                printf(" ");
            }
        }

        for (int k = 0; k < i + 1; k++) 
        {
            if (k == ultimaCarta)
            {
                printf("%d ", carta[k]->numero);
                printf("%d ", carta[k]->palo);
                for (int z = k; z < 30; z++)
                {
                    printf("%d ", carta[z]->numero);
                }
                ultimaCarta--;
            }
            else
                printf("* ");
        }
        
        printf("\n");
    }
    

}

void piramide(Map *jugadores)
{

    Stack *pila1 = stack_create();
    Stack *pila2 = stack_create(); 
    
    crearPila(pila1);
    crearPila(pila2);

    printf("\e[1;1H\e[2J");
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

    printf("\e[1;1H\e[2J");
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
    printf("\e[1;1H\e[2J");

    juegoPiramide(jugadores, cantidadJugadores, pila2);
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