#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <ios>

class Control{
private:
    bool UP;
    bool DOWN;
    bool RIGHT;
    bool LEFT;

public:
    Control(): UP(false), DOWN(false), RIGHT(false), LEFT(false) {};

    void pressButton(){
        system("cls");

        char mvnt;

        mvnt = getch();

        switch(mvnt){
        case 'w':
            UP = true;
            std::cout<<"UP"<<std::endl;
            break;

        case 's':
            DOWN = true;
            std::cout<<"DOWN"<<std::endl;
            break;

        case 'a':
            LEFT = true;
            std::cout<<"LEFT"<<std::endl;
            break;

        case 'd':
            RIGHT = true;
            std::cout<<"RIGHT"<<std::endl;
            break;
        }
    }

    void setDefaults(){
        UP = false;
        DOWN = false;
        RIGHT = false;
        LEFT = false;
    }
};

class Mapa{
private:
    int** plano;//26 x 18

public:
    Mapa(): plano(NULL) {};
    void createMap(){
        plano = new int*[18];
        for(int i=0;i<26;i++){
            plano[i] = new int[26];
        }
    }

    void generateMap(){
        FILE *p;
        std::fstream in;
        in.open("mapa.txt",ios::in);


        for(int i=0;i<18;i++){
            for(int j=0;j<26;j++){
                in>>plano[i][j];
            }
        }

        fclose(p);
    }

    void printMap(){
        for(int i=0;i<18;i++){
            for(int j=0;j<26;j++){
                std::cout<<plano[i][j];
            }
            std::cout<<std::endl;
        }
    }

    void destructMap(){
        for(int i=0;i<18;i++){
            delete[] plano[i];
        }
        delete[] plano;
    }

};

class Jugador{

};

int main(){

    /*Control myControl;

    while(true){
        myControl.pressButton();
        Sleep(50);
        myControl.setDefaults();
    }*/

    Mapa myMAP;

    myMap.createMap();
    myMap.generateMap();
    myMap.printMap();
    myMap.destructMap();

    return ;
}
