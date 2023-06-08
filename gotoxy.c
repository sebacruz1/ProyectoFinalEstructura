#include <stdio.h>
#include <windows.h> //Librería necesaria para manipular la consola de salida
#include <stdbool.h>
#include <stdlib.h>
#include "gotoxy.h"

/*La función recibe los parámetros x, y
* y situa el cursor en esa posicción */

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