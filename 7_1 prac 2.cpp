#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>

void vuelta(GrafoP<int>& G){
    for(size_t i=0; i<G.numVert();i++){
        for(size_t j=0; j<G.numVert(); j++){
            if(G[i][j]!=G.INFINITO && i!=j){
                G[i][j]*=-1;
            }
        }
    }
}
void vueltaM(matriz<int>& M){
    for(size_t i=0; i<M.size();i++){
        for(size_t j=0; j<M.size(); j++){
            if(M[i][j]!=typename GrafoP<int>::INFINITO && i!=j){
                M[i][j]*=-1;
            }
        }
    }
}

int maximo(GrafoP<int>& G, int &origen, int &destino){
    vuelta(G);
    matriz<typename GrafoP<int>::vertice> P;
    matriz<int> M=Floyd(G,P);
    vueltaM(M);
    int max=-G.INFINITO;
    for(size_t i=0; i<M.dimension(); i++){
        for(size_t j=0; j<M.dimension(); j++){
            if(M[i][j]!=typename GrafoP<int>::INFINITO && M[i][j]>max && i!=j ){
                max=M[i][j];
                origen=i;
                destino = j;
            }
        }
    }
    return max;
}