#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include "gotoxy.h"

//*FUNCIONES QUE MANEJAN LA FLECHA*
//------------------------------------------------------------------------------------------
/*La función recibe 3 parámetros, y esta se encarga de borrar la flecha.
* El primer y segundo parámetro representan la posición donde
* debería ir la PRIMERA flecha. El 3er parámetro es la cantidad
* de opciones del menu*/
void limpiarFlecha(int x, int y, int cantOpciones){
    for(int i = 0; i < cantOpciones; i++){
        gotoxy(x, y + i); 
        printf("   ");
    }
}

/*La función actualiza la variable opción para que se encuentre
* dentro del rango de [0 , cantOpciones - 1]*/
void formatearOpcion(int* opcion, int cantOpciones){
    *opcion = *opcion % 3;
    if(*opcion < 0) *opcion = 3 + *opcion;
}

/*La función recibe 3 parámetros, y esta se encarga de "pintar" la flecha.
* El primer y segundo parámetro representan la posición donde
* debería ir la PRIMERA flecha. El 3er parámetro es la opción actual*/
void ubicarFlecha(int x, int y, int opcion){
    gotoxy(x, y + opcion);
    printf("-->");
}

/*La función valida las teclas presionadas por el usuario
* y cambia la opción según estas. Retorna un valor booleano
* que por defecto es false, lo que significa que el usuario
* no ha escogido opción, pero en cuanto se presione enter, 
* la función retornará true, ya que ha escogido esa opción*/
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
    while(true){
        GetAllKeys();

        //Puede reemplazarse por alguna función que solo borre el menu
        //como lo hace el "limpiarFlecha()" y así obtener un menu integrado 
        //en el juego, como por ejemplo en Pokemon
        system("cls");

        gotoxy(10, 10); printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        gotoxy(10, 11); printf("|        MENU PRINCIPAL      |");
        gotoxy(10, 12); printf("|                            |");
        gotoxy(10, 13); printf("|              TOMANJI       |");
        gotoxy(10, 14); printf("|              PIRAMIDE      |");
        gotoxy(10, 15); printf("|              SALIR         |");
        
        gotoxy(10, 16); printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

        //Toda la lógica de como borrar y pintar la flecha
        while(true){
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
            exit(0); //Salir del programa
        } 
    }
}