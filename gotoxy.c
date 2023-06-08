#include <stdio.h>
#include <windows.h> //Librería necesaria para manipular la consola de salida
#include <stdbool.h>
#include <stdlib.h>
#include "gotoxy.h"
#define DELAY 20 //Tiempo de pausa entre cada imagen

//*Constantes propuestas*
#define G 2 //Gravedad
#define FLOAT 30 //Donde se situa el suelo en el eje y (recordad que esta invertido)

/*Struct con todas las características del jugador */
typedef struct{
    int x;
    int y;
    int vy;
    int vx;
}Player;

/*La función genera una instancia del jugador
* e inicializa sus variables */
Player* createPlayer(){
    Player* p = (Player*) malloc(sizeof(Player));
    p->x = 5;
    p->y = FLOAT;
    p->vy = 0;
    p->vx = 3;
    return p;
}

/*La función recibe los parámetros x, y
* y situa el cursor en esa posicción */
void gotoxy(int x, int y){
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    //Eje invertido, con y = 0 en la primera línea, y > 0 desde la segunda línea en adelante
    pos.Y = y; 
    SetConsoleCursorPosition(consola, pos);
}

/*Función que oculta el cursor. Si tiene dudas con esta existen
* variados sitios en internet de donde obtener documentación*/
void ocultarCursor(){
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursInfo;
    cursInfo.dwSize = 2;
    cursInfo.bVisible = FALSE;
    SetConsoleCursorInfo( consola, &cursInfo);
}

//*Función propuesta*
//Obtiene todas las teclas que se utilizan en el juego
void GetAllKeys(){
    GetAsyncKeyState(VK_SPACE);
    GetAsyncKeyState(VK_RIGHT);
    GetAsyncKeyState(VK_LEFT);
    GetAsyncKeyState(VK_RETURN);
}

//*Lógica propuesta*
/*La función contiene la lógica de como mover al jugador
* y lo que debería realizar con algunas teclas*/
void mover(Player* p){

    //Tecla: Barra espaciadora. Otorgar al jugador velocidad en el eje y
    //cuando la tecla se presione y se encuentre situado en el suelo
    if (GetAsyncKeyState(VK_SPACE) && p->y == FLOAT){
        p->vy = -9; //Es negativa ya que el eje esta invertido
    }

    //Tecla: flecha derecha. Movese a la derecha
    if (GetAsyncKeyState(VK_RIGHT)){
        p->x += p->vx;
    }

    //Tecla: flecha izquierda. Moverse a la izquierda
    if (GetAsyncKeyState(VK_LEFT)){
        p->x -= p->vx;
    }
    
    //Lógica de un salto, físicas de caída libre y mov. parabólico
    p->vy += G;
    p->y += p->vy;

    //Resetear posición y velocidad en caso de pasar más bajo que el suelo
    if(p->y > FLOAT){
        p->y = FLOAT;
        p->vy = 0;
    }
    
}

//*Función propuesta*
/*La función recibe al jugador*/
void render(Player* p){
    //Valida su movimiento
    mover(p);

    //Lo pinta en pantalla
    gotoxy(p->x, p->y);
    printf("*");
}


void game(){
    //*Función propuesta*
    //Resetea la lectura de teclas
    GetAllKeys();

    
    system("cls");
    printf("Para visualizar el ejemplo coloque pantalla completa\n");

    //Como su nombre lo indica, genera una pausa 
    //en el programa hasta pulsar alguna tecla
    system("pause");

    //Cambia el color de la terminal y las letras
    system("color 06");

    //Debería idealmente ocultar cursor, pero 
    //en ciertas ocasiones, no lográ ocultarlo
    ocultarCursor();

    //*Struct propuesta*
    //Genero la instancia jugador
    Player* p = createPlayer();

    while(true){

        //Sleep recibe un número entero en milisegundos, es decir cada 1000 es 1 segundo de espera
        //Sleep( DELAY );   

        //*Función propuesta*
        //La lógica del programa, los objetos que se pintarán y su orden, restricciones, etc
        render(p);

        //Se limpia el terminal, pero si solo desea limpiar una sección basta
        //con utilizar gotoxy en ese posición y printear espacios para borrar
        system("cls");      
    }

}

/*
Colores 
0 = Negro
1= Azul
2= Verde
3= Aguamarina
4= Rojo
5= Púrpura
6= Amarillo
7= Blanco
8= Gris
9= Azul Claro
A= Verde Claro
B= Aguamarina Claro
C= Rojo Claro
D= Púrpura Claro
E= Amarillo Claro
F= Blanco Brillante
*/