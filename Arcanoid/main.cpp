#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
class pelota{
    public:
    int x,y,vx,vy,radio;
    pelota(int myx,int myy,int myvx,int myvy,int myradio){
        x=myx;
        y=myy;
        vx=myvx;
        vy=myvy;
        radio=myradio;
    }
    void cambiarDir(int ancho,int alto, int xbarra,int xancho){
        if((x+vx-ancho+12)>0){
            if((x-ancho+12)<-1){
                vx=ancho-12-x;
            }else{
                vx=(rand()%5)-8;
            }
        }else if((x+vx)<0){
            if(x>1.0){
                vx=-x;
            }else{
                vx=(rand()%5)+3;
            }
        }
        if((y+vy-alto+50+radio*2)>0 && y+radio<360 && x>xbarra-radio&& x<xbarra+xancho+radio){
            if((y-alto+62)<-1){
                vy=ancho-62-y;
            }else{
                vy=(rand()%5)-8;
            }
        }else if((y+vy)<0){
            if(y>1.0){
                vy=-y;
            }else{
                vy=(rand()%5)+3;
            }
        }
    }
    void mover(){
        x+=vx;
        y+=vy;
    }
    void colisionBloques(int ** bloques,int n,int m,int ancho, int alto){
        int puntoinferior=y+(2*radio);
        int puntoderecho=x+(2*radio);
        int anchoBloque=ancho/m;
        int altoBloque=alto/(2*n);
        bool flag=true;
        for(int i=0; i<n;i++){
            for(int j=0;j<m;j++){
                if(bloques[i][j]&&flag){
                    if((x+(radio*5)/3)>=anchoBloque*j && (x+radio/3)<=anchoBloque*(j+1) && ((y>=altoBloque*i+(altoBloque/2) && y<=altoBloque*(i+1))|| (puntoinferior>=altoBloque*i && puntoinferior<=altoBloque*i+(altoBloque/2)))){
                        vy*=-1;
                        flag=false;
                    }
                    if((y+(radio*5)/3)>=altoBloque*i && (y+radio/3)<=altoBloque*(i+1) && ((x>=anchoBloque*(j+1)-(anchoBloque/5) && x<=anchoBloque*(j+1))|| (puntoderecho>=anchoBloque*j && puntoderecho<=anchoBloque*j+(anchoBloque/5)))){
                        vx*=-1;
                        flag=false;
                    }
                    if(!flag){
                        bloques[i][j]-=1;
                    }
                }
            }
        }
    }
    void colisionBloques2(int ** bloques,int n,int m,int ancho, int alto){
        int anchoBloque=ancho/m;
        int altoBloque=alto/(2*n);
        int x1=x/anchoBloque;
        int y1=y/altoBloque;
        int x2=(x+radio+radio)/anchoBloque;
        int y2=(y+radio+radio)/altoBloque;
        bool flag=false;
        if(y2<n){
            if (x1==x2){
                if(bloques[y1][x1]){
                    vy*=-1;
                    bloques[y1][x1]--;
                }else if(bloques[y2][x1]){
                    vy*=-1;
                    bloques[y2][x1]--;
                }else if(vy<0&&(y+vy/2)/altoBloque>=0&&bloques[(y+vy/2)/altoBloque][x1]){
                    //mover();
                    //Sleep(30);
                    bloques[(y+vy/2)/altoBloque][x1]=0;
                    vx*=-1;
                    vy*=-1;
                }else if(vy>0&&(y+vy/2+radio+radio)/altoBloque<n&&bloques[(y+radio+radio+vy/2)/altoBloque][x1]){
                    //mover();
                    //Sleep(30);
                    bloques[(y+radio+radio+vy/2)/altoBloque][x1]=0;
                    vx*=-1;
                    vy*=-1;
                }
            }else if(y1==y2){
                if(bloques[y1][x1]){
                    vx*=-1;
                    bloques[y1][x1]--;
                }else if(bloques[y1][x2]){
                    vx*=-1;
                    bloques[y1][x2]--;
                }
            }else{
                if(bloques[y1][x1]){
                    vx*=-1;
                    vy*=-1;
                    bloques[y1][x1]--;
                }else if(bloques[y1][x2]){
                    vx*=-1;
                    vy*=-1;
                    bloques[y1][x2]--;
                }else if(bloques[y2][x1]){
                    vx*=-1;
                    vy*=-1;
                    bloques[y2][x1]--;
                }else if(bloques[y2][x2]){
                    vx*=-1;
                    vy*=-1;
                    bloques[y2][x2]--;
                }
            }
        }
    }
};
class barra{
public:
    int x;
    int ancho;
    int direccion;
    barra(int myx,int myancho){
        x=myx;
        direccion=0;
        ancho=myancho;
    }
    void derecha(){
        direccion=1;
    }
    void izquierda(){
        direccion=-1;
    }
    void stop(){
        direccion=0;
    }
    void mover(){
        if(direccion<0 && x>9){
            x-=10;
        }else if(direccion>0 && x<391-ancho){
            x+=10;
        }
    }
};
using namespace std;
int main(){
    int alto=400,ancho=400,fps=30,bloquesx=8,bloquesy=10;
    pelota ball=pelota((ancho/2)-5,(alto)-55,4,4,6);
    barra jugador=barra(180,50);
    sf::RectangleShape bar;
    bar.setSize({50,10});
    bar.setPosition(180,350);
    int** matriz=new int*[bloquesy];
    for(int i=0;i<bloquesy;i++){
        matriz[i]=new int[bloquesx];
    }
    sf::RectangleShape bloques[bloquesy][bloquesx];
    for(int i=0;i<bloquesy;i++){
        for(int j=0;j<bloquesx;j++){
            matriz[i][j]=1;
            bloques[i][j].setSize({ancho/bloquesx,(alto/2)/bloquesy});
            bloques[i][j].setPosition((ancho/bloquesx)*j,((alto/2)/bloquesy)*i);
            bloques[i][j].setFillColor(sf::Color::Blue);
        }
    }

    //pelota ball2=pelota(0,0,13,13,10);
    sf::RenderWindow win(sf::VideoMode(ancho, alto), "SFML Test");
    sf::CircleShape circulo[5];
    circulo[0].setRadius(ball.radio);
    circulo[0].setFillColor(sf::Color::Red);
    //circulo[1].setRadius(ball.radio);
    //circulo[1].setFillColor(sf::Color::Red);

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            jugador.izquierda();
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            jugador.derecha();
        }else{
            jugador.stop();
        }
        ball.cambiarDir(ancho,alto,jugador.x,jugador.ancho);
        ball.mover();
        ball.colisionBloques2(matriz,bloquesy,bloquesx,ancho, alto);
        //ball2.cambiarDir(ancho,alto);
        //ball2.mover();
        win.clear();
        circulo[0].setPosition(ball.x,ball.y);
        jugador.mover();
        bar.setPosition(jugador.x,350);
        win.draw(circulo[0]);
        win.draw(bar);
        for(int i=0;i<bloquesy;i++){
            for(int j=0;j<bloquesx;j++){
                if(matriz[i][j]){
                    win.draw(bloques[i][j]);
                }
            }
        }
        //circulo[1].setPosition(ball2.x,ball2.y);
        //win.draw(circulo[1]);
        win.display();
        Sleep(1000/fps);
    }

    return 0;
}
