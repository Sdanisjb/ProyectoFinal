#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
class barra;
class pelota;

class poder{
public:
    int x,y;
    char tipo;
    sf::RectangleShape forma;
    poder*siguiente;
    poder(int myx,int myy,char mitipo);
    void dibujar(sf::RenderWindow &win);
    bool mover(int myx,int ancho,sf::RenderWindow &win,barra&jugador,pelota&ball);
};
class bala{
public:
    int x,y;
    sf::RectangleShape forma;
    bala *siguiente;
    bala(int myx,int myy);
    bool mover(sf::RenderWindow &win,char**poderes,int ** bloques,int n,int m,int ancho, int alto,poder*&power,barra&);
    bool colision(char**poderes,int ** bloques,int n,int m,int ancho, int alto,poder*&power,barra&);
};
class pelota{
public:
    int x,y,vx,vy,radio;
    sf::CircleShape circulo;
    pelota*siguiente;
    pelota(int myx,int myy,int myvx,int myvy,int myradio);
    bool cambiarDir(int ancho,int alto, int xbarra,int xancho);
    void mover();
    void dibujar(sf::RenderWindow &win);
    void duplicar();
    void colisionBloques2(int ** bloques,char**poderes,int n,int m,int ancho, int alto,poder*&power,barra&);
};
class barra{
public:
    int vidas;
    int puntos;
    int x;
    int ancho;
    int direccion;
    bool canon;
    sf::RectangleShape bar;
    barra(int myx,int myancho);
    void derecha();
    void izquierda();
    void stop();
    void dibujar(sf::RenderWindow &win);
    void xs();
    void xl();
    void canhon();
    void disparo(bala*&shot);
    void mover();
    bool reiniciar();
};
class Bloques{
public:
    bool haybloques;
    int bloquesx,bloquesy;
    int** matriz;
    char** poderes;
    sf::RectangleShape bloques[10][8];
    Bloques(int,int);
    void crearNivel(int);
    bool dibujar(sf::RenderWindow &);
};
class arcanoid{
public:
    int alto,ancho,fps,nivel;
    poder* power=NULL;
    Bloques matriz=Bloques(400,400);
    pelota *ball;
    barra jugador=barra(180,50);
    bala *ataque;
    int disparo;
    arcanoid(int,int,int);
    bool run(sf::RenderWindow &);
    void teclado();
    void guardarpuntos(std::string nombre);
};
#endif // HEADER_H_INCLUDED
