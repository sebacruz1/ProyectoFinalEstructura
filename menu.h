#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include "gotoxy.h"

#define FOREGROUND_DARK_BLUE  FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define FOREGROUND_YELLOW     FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_CYAN    FOREGROUND_GREEN | FOREGROUND_BLUE


void limpiarFlecha(int x, int y, int cantOpciones)
{
    for(int i = 0; i < cantOpciones; i++){
        gotoxy(x, y + i); 
        printf("   ");
    }
}

void setConsoleColor(WORD color) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, color);
}

void formatearOpcion(int* opcion, int cantOpciones)
{
    *opcion = *opcion % 3;
    if(*opcion < 0) *opcion = 3 + *opcion;
}

void ubicarFlecha(int x, int y, int opcion)
{
    gotoxy(x, y + opcion);
    printf("-->");
}

bool cambiarOpcion(int * opcion)
{
    Sleep(250);
    if( GetAsyncKeyState(VK_UP) )
    {
        *opcion -= 1;
    }
   
    if ( GetAsyncKeyState(VK_DOWN) )
    {
        *opcion += 1;
    }
    if ( GetAsyncKeyState(VK_RETURN) )
    {
        return true;
    }
    return false;
}

void subrutina()
{
    GetAllKeys();
    system("cls");
    gotoxy(10, 10); printf("Ejemplo de subrutina que se puede");
    gotoxy(10, 11); printf("realizar, sin salir del propio menu");
    gotoxy(10, 12); system("pause");
}


int menu()
{
    int opcion = 0;

    gotoxy(10,10);printf("BIENVENIDOS A \n\n\n");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    gotoxy(10,11);printf(" /$$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$   /$$$$$$  /$$$$$$$$  /$$$$$$              /$$\n");      
    gotoxy(10,12);printf("| $$__  $$ /$$__  $$| $$$    /$$$| $$__  $$ /$$__  $$|_____ $$  /$$__  $$            | $$\n");   
    setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    gotoxy(10,13);printf("| $$  \\ $$| $$  \\ $$| $$$$  /$$$$| $$  \\ $$| $$  \\ $$     /$$/ | $$  \\ $$            | $$\n");       
    gotoxy(10,14);printf("| $$$$$$$ | $$  | $$| $$ $$/$$ $$| $$$$$$$ | $$$$$$$$    /$$/  | $$  | $$            | $$\n");         
    setConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);         
    gotoxy(10,15);printf("| $$__  $$| $$  | $$| $$  $$$| $$| $$__  $$| $$__  $$   /$$/   | $$  | $$            |__/\n");      
    gotoxy(10,16);printf("| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$  \\ $$| $$  | $$  /$$/    | $$  | $$\n");                      
    gotoxy(10,17);printf("| $$$$$$$/|  $$$$$$/| $$ \\/  | $$| $$$$$$$/| $$  | $$ /$$$$$$$$|  $$$$$$/             /$$\n");                            
    gotoxy(10,18);printf("|_______/  \\______/ |__/     |__/|_______/ |__/  |__/|________/ \\______/             |__/\n"); 

    
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    
                                                                                                                       
                                                                                    

    system("pause");
    

    while(true)
    {
        GetAllKeys();
        system("cls");
        setConsoleColor(FOREGROUND_DARK_BLUE);
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