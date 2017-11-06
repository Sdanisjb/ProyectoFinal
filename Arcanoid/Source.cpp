#include "header/header.h"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
bala::bala(int myx,int myy){
    x=myx;
    y=myy;
    siguiente=NULL;
    forma.setSize({4,10});
}
bool bala::mover(sf::RenderWindow &win,char**poderes,int ** bloques,int n,int m,int ancho, int alto,poder*&power,barra&player){
    y-=10;
    forma.setPosition(x,y);
    win.draw(forma);

    if(siguiente!=NULL){
        if(siguiente->mover(win,poderes,bloques,n,m,ancho,alto,power,player)){
            if(siguiente->siguiente==NULL){
                delete siguiente;
                siguiente=NULL;
            }else{
                bala *aux=siguiente;
                siguiente=siguiente->siguiente;
                delete aux;
                siguiente=NULL;
            }
        }
    }
    return colision(poderes,bloques,n,m,ancho,alto,power,player);
}
bool bala::colision(char**poderes,int ** bloques,int n,int m,int ancho, int alto,poder*&power,barra&player){
    if(y<-10){
        return true;
    }
    int anchoBloque=ancho/m;
    int altoBloque=alto/(2*n);
    int x1=x/anchoBloque;
    int y1=y/altoBloque;
    int x2=(x+4)/anchoBloque;
    int y2=(y+10)/altoBloque;
    int xaux=-10,yaux=-10;
    if(y2<n){
        if(bloques[y1][x1]){
            yaux=y1;
            xaux=x1;
        }else if(bloques[y2][x1]){
            yaux=y2;
            xaux=x1;
        }else if(bloques[y1][x2]){
            yaux=y1;
            xaux=x2;
        }else if(bloques[y2][x2]){
            yaux=y2;
            xaux=x2;
        }
    }
    if(xaux>-10){
            player.puntos+=10;
        bloques[yaux][xaux]--;
        if(!bloques[yaux][xaux]){
            poder**aux=&power;
            if(power!=NULL){
                while((*aux)!=NULL){
                    aux=&((*aux)->siguiente);
                }
            }
            if(poderes[yaux][xaux]=='l'){
                (*aux)=new poder(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'l');
            }else if(poderes[yaux][xaux]=='s'){
                (*aux)=new poder(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'s');
            }else if(poderes[yaux][xaux]=='c'){
                (*aux)=new poder(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'c');
            }else if(poderes[yaux][xaux]=='m'){
                (*aux)=new poder(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'m');
            }
        }
        return true;
    }
    return false;
}
poder::poder(int myx,int myy,char mitipo){
    x=myx;
    y=myy;
    forma.setSize({8,20});
    tipo=mitipo;
    siguiente=NULL;
    if(tipo=='s'){
        forma.setFillColor(sf::Color::Red);
    }else if(tipo=='l'){
        forma.setFillColor(sf::Color::Green);
    }else if(tipo=='m'){
        forma.setFillColor(sf::Color::Magenta);
    }else if(tipo=='c'){
        forma.setFillColor(sf::Color::Cyan);
    }
}
void poder::dibujar(sf::RenderWindow &win){
    forma.setPosition(x,y);
    win.draw(forma);
}
bool poder::mover(int myx,int ancho,sf::RenderWindow &win,barra&jugador,pelota&ball){
    y+=5;
    dibujar(win);
    if (siguiente!=NULL){
        if(siguiente->mover(myx,ancho,win,jugador,ball)){
            if(siguiente->siguiente!=NULL){
                poder*aux=siguiente->siguiente;
                siguiente->siguiente=NULL;
                delete siguiente;//Colocar destructor
                siguiente=aux;
            }else{
                delete siguiente;//Colocar destructor
                siguiente=NULL;
            }
        }
    }
    if(x>myx-8&&x<myx+ancho&&y>330&&y<360){
        if(tipo=='s'){
            jugador.xs();
        }else if(tipo=='l'){
            jugador.xl();
        }else if(tipo=='c'){
            jugador.canhon();
        }else if(tipo=='m'){
            ball.duplicar();
        }
        return true;
    }else if (y>400){
        return true;
    }
    return false;
}

pelota::pelota(int myx,int myy,int myvx,int myvy,int myradio){
    x=myx;
    y=myy;
    if (!myvx||!myvy){
        srand ((int)(((double)clock())*100));
        vx=(rand()%5)+3;
        vy=(rand()%5)-8;
    }else{
        vx=myvx;
        vy=myvy;
    }
    radio=myradio;
    circulo.setRadius(radio);
    circulo.setFillColor(sf::Color::Red);
    siguiente=NULL;
}
bool pelota::cambiarDir(int ancho,int alto, int xbarra,int xancho){
    if(siguiente!=NULL){
        if(siguiente->cambiarDir(ancho,alto,xbarra,xancho)){
            if(siguiente->siguiente==NULL){
                delete siguiente;//Colocar destructor
                siguiente=NULL;
            }else{
                pelota*aux;
                aux=siguiente->siguiente;
                delete siguiente;//Colocar destructor
                siguiente=aux;
            }
        }
    }
    srand ((int)(((double)clock())*100));
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
    if(y>alto){
        x=(ancho/2)-12;
        y=alto-62;
        vx=-5;
        vy=-5;
        return true;
    }else if((y+vy)<0){
        if(y>1.0){
            vy=-y;
        }else{
            vy=(rand()%5)+3;
        }
    }else if((y+vy-alto+50+radio*2)>0 && y+radio<360 && x>xbarra-radio&& x<xbarra+xancho+radio){
        if((y-alto+62)<-1){
            vy=ancho-62-y;
        }else{
            vy=(rand()%5)-8;
        }
    }
    return false;
}
void pelota::mover(){
    x+=vx;
    y+=vy;
    if(siguiente!=NULL){
        siguiente->mover();
    }
}
void pelota::dibujar(sf::RenderWindow &win){
    circulo.setPosition(x,y);
    win.draw(circulo);
    if(siguiente!=NULL){
        siguiente->dibujar(win);
    }
}
void pelota::duplicar(){
    if(siguiente==NULL){
        siguiente=new pelota(x,y,vx*-1,vy,radio);
    }else{
        pelota*aux=siguiente;
        siguiente=new pelota(x,y,vx*-1,vy,radio);
        siguiente->siguiente=aux;
        aux->duplicar();
    }
}
void pelota::colisionBloques2(int ** bloques,char**poderes,int n,int m,int ancho, int alto,poder*&power,barra&player){
    int anchoBloque=ancho/m;
    int altoBloque=alto/(2*n);
    int x1=x/anchoBloque;
    int y1=y/altoBloque;
    int x2=(x+radio+radio-2)/anchoBloque;
    int y2=(y+radio+radio-2)/altoBloque;
    int xaux=-10,yaux=-10;
    if(y2<n){
        if (x1==x2){
            if(bloques[y1][x1]){
                vy*=-1;
                xaux=x1;
                yaux=y1;
            }else if(bloques[y2][x1]){
                vy*=-1;
                xaux=x1;
                yaux=y2;
            }else if(vy<0&&(y+vy/2)/altoBloque>=0&&bloques[(y+vy/2)/altoBloque][x1]){
                xaux=x1;
                yaux=(y+vy/2)/altoBloque;
                vx*=-1;
                vy*=-1;
            }else if(vy>0&&((y+vy/2+radio+radio)/altoBloque)<n-1&&bloques[(y+radio+radio+vy/2)/altoBloque][x1]){
                xaux=x1;
                yaux=(y+radio+radio+vy/2)/altoBloque;
                vx*=-1;
                vy*=-1;
            }
        }else if(y1==y2){
            if(bloques[y1][x1]){
                vx*=-1;
                xaux=x1;
                yaux=y1;
            }else if(bloques[y1][x2]){
                vx*=-1;
                xaux=x2;
                yaux=y1;
            }
        }else{
            if(bloques[y1][x1]){
                vx=abs(vx);
                vy=abs(vy);
                xaux=x1;
                yaux=y1;
            }else if(bloques[y1][x2]){
                vx=-abs(vx);
                vy=abs(vy);
                xaux=x2;
                yaux=y1;
            }else if(bloques[y2][x1]){
                vx=abs(vx);
                vy=-abs(vy);
                xaux=x1;
                yaux=y2;
            }else if(bloques[y2][x2]){
                vx=-abs(vx);
                vy=-abs(vy);
                xaux=x2;
                yaux=y2;
            }
        }
    }
    if(xaux>-10){
        player.puntos+=10;
        bloques[yaux][xaux]--;
        if(!bloques[yaux][xaux]){
            poder**aux=&power;
            if(power!=NULL){
                while((*aux)!=NULL){
                    aux=&((*aux)->siguiente);
                }
            }
            if(poderes[yaux][xaux]=='l'){
                (*aux)=new poder(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'l');
            }else if(poderes[yaux][xaux]=='s'){
                (*aux)=new poder(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'s');
            }else if(poderes[yaux][xaux]=='c'){
                (*aux)=new poder(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'c');
            }else if(poderes[yaux][xaux]=='m'){
                (*aux)=new poder(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'m');
            }
        }
    }
    if(siguiente!=NULL){
        siguiente->colisionBloques2(bloques,poderes,n,m,ancho,alto,power,player);
    }
}


barra::barra(int myx,int myancho){
    puntos=0;
    vidas=3;
    x=myx;
    direccion=0;
    ancho=myancho;
    bar.setSize({50,10});
    bar.setPosition(175,350);
    canon=false;
}
void barra::derecha(){
    direccion=1;
}
void barra::izquierda(){
    direccion=-1;
}
void barra::stop(){
    direccion=0;
}
void barra::dibujar(sf::RenderWindow &win){
    bar.setPosition(x,350);
    win.draw(bar);
}
void barra::xs(){
    if (ancho>30){
        ancho-=14;
        bar.setSize({ancho,10});
        x+=7;
    }
}
void barra::xl(){
    if (ancho<70){
        ancho+=14;
        bar.setSize({ancho,10});
        x-=7;
    }
}
void barra::canhon(){
    canon=true;
}
void barra::disparo(bala*&shot){
    if(shot==NULL){
        shot=new bala(x+ancho/2,350);
    }
    else{
        disparo(shot->siguiente);
    }
}
void barra::mover(){
    if(direccion<0 && x>4){
        x-=10;
    }else if(direccion>0 && x<396-ancho){
        x+=10;
    }
}
bool barra::reiniciar(){
    vidas--;
    if(!vidas){
        return true;
    }
    ancho=50;
    canon=false;
    bar.setSize({50,10});
    x=200-(ancho/2);
    bar.setPosition(175,350);
    return false;
}

Bloques::Bloques(int ancho, int alto){
    haybloques=false;
    bloquesx=8;
    bloquesy=10;
    matriz=new int*[bloquesy];
    poderes=new char*[bloquesy];
    for(int i=0;i<bloquesy;i++){
        matriz[i]=new int[bloquesx];
        poderes[i]=new char[bloquesx];
        for(int j=0;j<bloquesx;j++){
            bloques[i][j].setSize({ancho/bloquesx,(alto/2)/bloquesy});
            bloques[i][j].setPosition((ancho/bloquesx)*j,((alto/2)/bloquesy)*i);
        }
    }
}
void Bloques::crearNivel(int nivel=1){

    for(int i=0;i<bloquesy;i++){
        for(int j=0;j<bloquesx;j++){
            if(rand()%15==0){
                poderes[i][j]='l';
            }else if(rand()%15==1){
                poderes[i][j]='s';
            }else if(rand()%15==2){
                poderes[i][j]='m';
            }else if(rand()%15==3){
                poderes[i][j]='c';
            }
            if (nivel==1){
                if(/*i>0*/i>3 && i<bloquesy-3/*1*/&&j>0&&j<bloquesx-1){
                    matriz[i][j]=1;
                }else{
                    poderes[i][j]=0;
                    matriz[i][j]=0;
                }
            }else if (nivel==2){
                if(i>0 && i<bloquesy-1&&j>0&&j<bloquesx-1){
                    matriz[i][j]=1;
                }else{
                    matriz[i][j]=0;
                    poderes[i][j]=0;
                }
            }else if (nivel==3){
                if(i>1 && i<bloquesy-2&&j>1&&j<bloquesx-2){
                    matriz[i][j]=1;
                }else if(i>0 && i<bloquesy-1&&j>0&&j<bloquesx-1){
                    matriz[i][j]=2;
                }else{
                    matriz[i][j]=0;
                    poderes[i][j]=0;
                }
            }
        }
    }
}
bool Bloques::dibujar(sf::RenderWindow &win){
    haybloques=false;
    for(int i=0;i<bloquesy;i++){
        for(int j=0;j<bloquesx;j++){
            if(matriz[i][j]){
                if(matriz[i][j]==1){
                    bloques[i][j].setFillColor(sf::Color::Blue);
                }
                else if(matriz[i][j]==2){
                    bloques[i][j].setFillColor(sf::Color::Green);
                }if(matriz[i][j]==3){
                    bloques[i][j].setFillColor(sf::Color::Yellow);
                }
                win.draw(bloques[i][j]);
                haybloques=true;
            }
        }
    }
    return haybloques;
}

arcanoid::arcanoid(int myalto,int myancho,int myfps){
    alto=myalto;
    ancho=myancho;
    fps=myfps;
    nivel=1;
    power=NULL;
    ball=new pelota((ancho/2)-6,(alto)-62,0,0,6);
    matriz.crearNivel(nivel);
    ataque=NULL;
    disparo=0;
}
void arcanoid::teclado(){
    if(jugador.canon){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!disparo){
            jugador.disparo(ataque);
            disparo=15;
        }else{
            if (disparo>0)
                disparo--;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        jugador.izquierda();
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        jugador.derecha();
    }else{
        jugador.stop();
    }
}
void arcanoid::guardarpuntos(std::string nombre){
    std::string alm;
    std::string *nombres=new std::string[10];
    int *puntajes=new int[10];
    int cont=0;
    std::ifstream archivol("datos.txt");
    std::string cadena;
    while(!archivol.eof()) {
        archivol >> cadena;
        nombres[cont]=cadena;
        archivol >> cadena;
        puntajes[cont]=atoi(cadena.c_str());
        cont++;
    }
    if(cont==10){
        cont--;
    }
    nombres[cont]=nombre;
    puntajes[cont]=jugador.puntos;
    std::cout<<"Puntajes:\n";
    for(int i=0;i<=cont;i++){
        int imayor=i;
        for(int j=i+1;j<=cont;j++){
            if(puntajes[j]>puntajes[imayor]){
                imayor=j;
            }
        }
        if(imayor!=i){
            int aux=puntajes[i];
            std::string sAux=nombres[i];
            puntajes[i]=puntajes[imayor];
            nombres[i]=nombres[imayor];
            puntajes[imayor]=aux;
            nombres[imayor]=sAux;
        }
        alm+=nombres[i];
        alm+="\n";
        std::stringstream ss;
        ss << puntajes[i];
        ss >> cadena;
        alm+=cadena;
        if(i<cont)
            alm+="\n";
        std::cout<< i+1<<") "<<nombres[i]<<"\t"<< puntajes[i]<<"\n";
    }
    archivol.close();
    std::ofstream archivo;
    archivo.open("datos.txt");
    archivo << alm;
    archivo.close();
    delete[]puntajes;
    delete[]nombres;
}
bool arcanoid::run(sf::RenderWindow &win){
    teclado();
    ball->mover();
    ball->colisionBloques2(matriz.matriz,matriz.poderes,matriz.bloquesy,matriz.bloquesx,ancho, alto,power,jugador);
    if(ball->cambiarDir(ancho,alto,jugador.x,jugador.ancho)){
        if (ball->siguiente==NULL)
            if(jugador.reiniciar()){
                std::cout<<"Tu puntaje fue: "<<jugador.puntos<<"\n";
                return true;
            }else{
            }
        else{
            pelota*aux=ball->siguiente;
            delete ball;//Colocar destructor
            ball=aux;
        }
    }
    jugador.mover();
    win.clear();
    if (ataque!=NULL){
        if(ataque->mover(win,matriz.poderes,matriz.matriz,matriz.bloquesy,matriz.bloquesx,ancho, alto,power,jugador)){
            if(ataque->siguiente==NULL){
                delete ataque;
                ataque=NULL;
            }else{
                bala*aux=ataque;
                ataque=ataque->siguiente;
                delete aux;
            }
        }
    }
    jugador.dibujar(win);
    ball->dibujar(win);
    if(power!=NULL){
        if(power->mover(jugador.x,jugador.ancho,win,jugador,*ball)){
            if(power->siguiente!=NULL){
                poder*aux=power->siguiente;
                power->siguiente=NULL;
                delete power;//Colocar destructor
                power=aux;
            }else{
                delete power;//Colocar destructor
                power=NULL;
            }
        }
    }
    if(!matriz.dibujar(win)){
        nivel++;
        matriz.crearNivel(nivel);
    }
    win.display();
    Sleep(1000/fps);
    return false;
}
