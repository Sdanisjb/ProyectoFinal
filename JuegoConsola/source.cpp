#include <SFML/Audio.hpp>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

using namespace std;

void gotoxy(int x, int y)
{
    HANDLE hCon;  //Creando un identificador
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); //Recuperar el identificador de la consola
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}

void OcultarCursor()
{
    HANDLE hCon;  //Creando un identificador
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); //Recuperar el identificador de la consola
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon, &cci);
}

void color(int X)
{
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),X);
}

void bordes()
{
    for(int i = 2; i<78 ; i++)
    {
        gotoxy(i,3); cout << (char)178;
        gotoxy(i,33); cout << (char)178;
    }

    for(int i = 4; i<33 ; i++)
    {
        gotoxy(2,i); cout << (char)186;
        gotoxy(77,i); cout << (char)186;
    }

    gotoxy(2,3); cout << (char)201;
    gotoxy(2,33); cout << (char)200;
    gotoxy(77,3); cout << (char)187;
    gotoxy(77,33); cout << (char)188;
}

class Nave
{
    private:
        int x,y;
        int corazones;
        int vidas;
    public:
        Nave(int _x, int _y, int _corazones, int _vidas): x(_x), y(_y), corazones(_corazones), vidas(_vidas){} //CONSTRUCTOR
        int X(){return x;}/*Metodos para acceder a la coordenada X*/
        int Y(){return y;}/*Metodos para acceder a la coordenada Y*/
        int VID(){return vidas;}
        void COR() {corazones--;}/*Funcion que hace que corazones disminuya */
        void dibujar();
        void borrar();
        void volar();
        void pintarcorazones();
        void morir();
};

void Nave::dibujar()
{
    color(13);
    gotoxy(x,y);   cout << "  " << (char)30 << "  ";
    gotoxy(x,y+1); cout << " " << (char)4 << (char)169 << (char)4 <<" ";
    gotoxy(x,y+2); cout << (char)17 << (char)201 << " " << (char)187 << (char)16;
}

void Nave::borrar()
{
    gotoxy(x,y);   cout << "     ";
    gotoxy(x,y+1); cout << "     ";
    gotoxy(x,y+2); cout << "     ";
}

void Nave::volar()
{
     if (_kbhit())
     {
        int velocidad = 3;
        char tecla = getch();
        borrar();
        if(tecla == IZQUIERDA && x > 4) x-= velocidad;
        if(tecla == DERECHA && x+5 < 76) x += velocidad;
        if(tecla == ARRIBA && y > 6) y -= velocidad;
        if(tecla == ABAJO && y+3 < 32) y += velocidad;
        pintarcorazones();

     }

    dibujar();
}

void Nave::pintarcorazones()
{
    color(14);
    gotoxy(50,2); cout << "VIDAS -> " << vidas;
    gotoxy(64,2); cout << "SALUD";
    gotoxy(70,2); cout << "      ";
    for(int i = 0; i<corazones; i++)
    {

        color(12);
        gotoxy(70+i,2); cout << (char)3;
    }
}


void Nave::morir()
{
    if(corazones == 0)
    {
        color(12);
        borrar();
        gotoxy(x,y);   cout << "  **  ";
        gotoxy(x,y+1); cout << " **** ";
        gotoxy(x,y+2); cout << "  **  ";
        Sleep(300);

        color(14);
        borrar();
        gotoxy(x,y);   cout << "  **  ";
        gotoxy(x,y+1); cout << " **** ";
        gotoxy(x,y+2); cout << "  **  ";
        Sleep(200);

        borrar();
        vidas--;
        corazones = 3;
        pintarcorazones();
        dibujar();
    }

}


class Ast
{
    private:
        int x,y;
    public:
        Ast(int _x, int _y):x(_x), y(_y){}
        void pintar();
        void mover();
        /*Detecta la coordenada de cada uno de los asterorides con la nave de acuerdo a la posicion*/
        void choque(class Nave &nave);/*Se pasa por referencia porque se van a estar modificando los valores*/
        /* Le pasamos un objeto para acceder a sus metodos*/

};

void Ast::pintar()
{
    color(11);
    gotoxy(x,y); cout << (char)201 << (char)2 << (char)187 ;
}

void Ast::mover()
{
    gotoxy(x,y); cout << "   ";
    int velocidad = 2;
    y+= velocidad;
    if(y > 32)
    {
        x = rand()%71 + 4;//numero entre 0 + 4 y 71 + 4
        y = 4;
    }
    pintar();
}

void Ast::choque(class Nave &nave)
{
    if(x >= nave.X()/*mas a la izquierda*/ && x < nave.X()+5/*mas a la derecha*/ && y >= nave.Y()/*mas arriba*/ && y <= nave.Y()+2/*mas abajo*/)
    {
        nave.COR();
        nave.dibujar();
        nave.pintarcorazones();
        x = rand()%71 + 4;//numero entre 0 + 4 y 71 + 4
        y = 4;

    }
}

int main()
{
    sf::Music music;
    if (!music.openFromFile("msc.ogg"))
    return -1;
    music.play();
    OcultarCursor();
    bordes();
    Nave n(37,30,3,3);
    n.dibujar();
    n.pintarcorazones();
    int puntos = 0;
    string nombre;

    Ast a(10,4), a2(20,8), a3(50,6), a4(70,5), a5(30,5);

    bool finJuego = false;
    while(!finJuego)
    {


        color(14);
        gotoxy(3,2);
        puntos += 1;
        cout << "PUNTAJE --> " << puntos;

        a.mover();
        a.choque(n);
        a2.mover();
        a2.choque(n);
        a3.mover();
        a3.choque(n);
        a4.mover();
        a4.choque(n);
        a5.mover();
        a5.choque(n);


        if(n.VID() == 0)
        {
            finJuego = true;
            puntos +=0;
            system("cls");
            music.pause();
            cout << "Tu nombre --> ";
            cin >> nombre;
        }

        n.morir();
        n.volar();
        Sleep(30);

    }
    system("cls");
    system("color 0A");
    gotoxy(32,2);
    cout << nombre << " " << puntos << "\n\n";

    gotoxy(20,4);
    cout << "PERDISTE HERMANO SUERTE A LA PROXIMA \n";
    gotoxy(20,5);
    cout << "PERDISTE HERMANO SUERTE A LA PROXIMA \n";
    gotoxy(20,6);
    cout << "PERDISTE HERMANO SUERTE A LA PROXIMA \n";
    gotoxy(20,7);
    cout << "PERDISTE HERMANO SUERTE A LA PROXIMA \n";
    gotoxy(20,8);
    cout << "PERDISTE HERMANO SUERTE A LA PROXIMA \n";
    return 0;
}


