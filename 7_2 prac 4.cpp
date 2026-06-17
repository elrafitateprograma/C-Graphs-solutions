#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>



struct casilla{
    GrafoP<int>::vertice x,y;
    casilla(GrafoP<int>::vertice o, GrafoP<int>::vertice d): x(o), y(d){}
};

struct celda{
    casilla o,d;
};

casilla conVertCasilla(int i, int N){
    return casilla(i/N,i%N);
}
typename GrafoP<int>::vertice conCasillaVert(casilla c, int N){
    return (c.x*N+c.y);
}

bool esvalido(casilla o, casilla d){
    return (std::abs(o.x - d.x) + std::abs(o.y-d.y))==1;
}

template <typename T>
typename GrafoP<T>::tCamino laberinto(const int N, std::vector<celda> celdas, casilla o, casilla d, int *coste){
    GrafoP<T> G(N*N);
    for(size_t i=0; i<G.numVert(); i++){
        for(size_t j=0; j<G.numVert(); j++){
            if(i!=j){
                if(esvalido(convVertCasilla(i, N),convVertCasilla(j, N))){
                    G[i][j]=1;
                }
                else{
                    G[i][j]=G.INFINITO;
                }
            }
            else{
                G[i][j]=0;
            }
        }
    }
    for(size_t i=0; i<celdas.size(); i++){
        G[conCasillaVert(celdas[i].o,N)][conCasillaVert(celdas[i].d,N)]=G.INFINITO;
        G[conCasillaVert(celdas[i].d,N)][conCasillaVert(celdas[i].o,N)]=G.INFINITO;
    }
    std::vector<typename GrafoP<T>::vertice> vec2;
    std::vector<T> vec=Dijkstra(G,conCasillaVert(o,N),vec2);
    *coste=vec[conCasillaVert(d,N)];
    typename GrafoP<T>::tCamino C=camino(conCasillaVert(o,N), conCasillaVert(d,N), G);
    return C;
}