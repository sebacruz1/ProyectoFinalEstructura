#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stack.h"


/* Baraja de cartas */
/* ---------------- */

#define PALOS 4
#define NUMEROS 14
#define CARTAS (NUMEROS*PALOS)

typedef enum Palo 
{
    Pica,
    Corazon,
    Trebol,
    Diamante
} Palo;

typedef struct Carta 
{
    Palo palo;
    int  numero;
} Carta;

typedef Carta Baraja[CARTAS];


void inicializarBaraja(Baraja baraja)
{
    int i, j;

    for (i = 0; i < PALOS; i++)
    {
        for (j = 0; j < NUMEROS; j++)
        {
            baraja[NUMEROS * i + j].palo = (Palo)i;
            baraja[NUMEROS * i + j].numero = j;
        }
    }
}

void intercambiar (Carta *c1, Carta *c2)
{
    Carta aux;

    aux = *c1;
    *c1 = *c2;
    *c2 = aux;
}

void barajar (Baraja baraja)
{
  int cambios;
  int i,c1,c2;

  srand(time(NULL));

  cambios = 20 + (rand() % 1000);

  for (i=0; i<cambios; i++) 
  {

      c1 = rand() % CARTAS;
      c2 = rand() % CARTAS;

      intercambiar( &(baraja[c1]), &(baraja[c2]) );
  }

}

void stackCartas(Baraja baraja, Stack *pila)
{
    int i;

    for (i=0; i<CARTAS; i++)
    {
        char *a = strcpy(a, baraja[i].numero);
        a = strcpy(a, "de");
        a = strcpy(a, baraja[i].palo);
        stack_push(pila, a);
    }
        
}
