#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include "header/header.h"
#include <fstream>

using namespace std;
int main(){
    int ancho=400,alto=400,fps=33;
    arcanoid arc(alto,ancho,fps);
    sf::RenderWindow win(sf::VideoMode(ancho, alto), "SFML Test");
    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win.close();
            }
        }
        if(arc.run(win)){
            win.close();
            cout<<"Ingresa tu nombre";
            string nombre;
            cin>>nombre;
            arc.guardarpuntos(nombre);
        }
    }

    return 0;
}
