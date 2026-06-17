#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>
struct puentes{
    int o,d;
};

template <typename T>
matriz<T> islas(GrafoP<T> &G1, GrafoP<T> &G2, GrafoP<T> &G3, std::vector<puentes> p){
    GrafoP<T> G(G1.numVert()+G2.numVert()+G3.numVert());
    for(size_t i=0; i<G1.numVert(); i++){
        for(size_t j=0; j<G1.numVert(); j++){
            G[i][j]=G1[i][j];
        }
    }
    for(size_t i=G1.numVert(); i<G2.numVert(); i++){
        for(size_t j=G1.numVert(); j<G2.numVert(); j++){
            G[i][j]=G2[i-G1.numVert()][j-G1.numVert()];
        }
    }
    for(size_t i=G2.numVert(); i<G.numVert(); i++){
        for(size_t j=G2.numVert(); j<G.numVert(); j++){
            G[i][j]=G3[i-G1.numVert()-G2.numVert()][j-G1.numVert()-G2.numVert()];
        }
    }
    for(size_t i=0; i<p.size(); i++){
        G[p[i].o][p[i].d]=0;
        G[p[i].d][p[i].o]=0;
    }
    matriz<T> M(G.numVert());
    matriz<typename GrafoP<T>::vertice> P;
    M=Floyd(G,P);
    return M;
}