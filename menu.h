#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include "gotoxy.h"

void limpiarFlecha(int x, int y, int cantOpciones){
    for(int i = 0; i < cantOpciones; i++){
        gotoxy(x, y + i); 
        printf("   ");
    }
}

void formatearOpcion(int* opcion, int cantOpciones){
    *opcion = *opcion % 3;
    if(*opcion < 0) *opcion = 3 + *opcion;
}

void ubicarFlecha(int x, int y, int opcion){
    gotoxy(x, y + opcion);
    printf("-->");
}

bool cambiarOpcion(int * opcion){
    Sleep(250);
    if( GetAsyncKeyState(VK_UP) ){
        *opcion -= 1;
    }
    if( GetAsyncKeyState(VK_DOWN) ){
        *opcion += 1;
    }
    if( GetAsyncKeyState(VK_RETURN) ){
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------------------

/*La función muestra de ejemplo una subrutina dentro del menu.
* Luego de ejecutarse se regresa al menu, estas subrutinas pueden ser
* para cambiar de color la pantalla, mostrar highscores, instrucciones
* o hasta ejecutar sub-menus*/
void subrutina(){
    GetAllKeys();
    system("cls");
    gotoxy(10, 10); printf("Ejemplo de subrutina que se puede");
    gotoxy(10, 11); printf("realizar, sin salir del propio menu");
    gotoxy(10, 12); system("pause");
}

/*La función es un prototipo de menu interactivo. Puede recibir
* las propiedades del juego para cambiar las características*/
int menu(){
    int opcion = 0;
    while(true)
    {
        GetAllKeys();

        system("cls");

        gotoxy(10, 10); printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        gotoxy(10, 11); printf("|        MENU PRINCIPAL      |");
        gotoxy(10, 12); printf("|                            |");
        gotoxy(10, 13); printf("|              TOMANJI       |");
        gotoxy(10, 14); printf("|              PIRAMIDE      |");
        gotoxy(10, 15); printf("|              SALIR         |");
        
        gotoxy(10, 16); printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

        while(true)
        {
            limpiarFlecha(20, 13, 3);
            formatearOpcion(&opcion, 3);
            ubicarFlecha(20, 13, opcion);
            if(cambiarOpcion(&opcion)) break;
        }

        switch (opcion)
        {
        case 0:
             return 1;
        case 1:
            return 2;
            break;
        case 2:
            printf("Saliendo!"); 
            exit(0); 
        } 
    }
}