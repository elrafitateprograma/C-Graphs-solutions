#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>

template <typename T>

std::pair<int,int> islas(GrafoP<T> &F, GrafoP<T> &D, std::vector<typename GrafoP<T>::vertice> Fcos,std::vector<typename GrafoP<T>::vertice> Dcos){
    matriz<typename GrafoP<T>::vertice> P1,P2;
    matriz<T> MF=Floyd(F,P1);
    matriz<T> MD = Floyd(D,P2);
    T minF=F.INFINITO;
    int posF;
    for(size_t i=0; i<Fcos.size(); i++){
        T coste=0;
        for(size_t j=0; j<F.numVert(); j++){
            if(MF[Fcos[i]][j]!=F.INFINITO){
                coste=coste + MF[Fcos[i]][j];
            }
            
            
        }
        if(coste<minF){
            posF=cosF[i];
            minF=coste;
        }
    }
    T minD=F.INFINITO;
    int posD;
    for(size_t i=0; i<Dcos.size(); i++){
        T coste=0;
        for(size_t j=0; j<D.numVert(); j++){
            if(MD[Dcos[i]][j]!=D.INFINITO){
                coste=coste + MD[Dcos[i]][j];
            }
            
            
        }
        if(coste<minF){
            posD=Dcos[i];
            minD=coste;
        }
    }
    return {posF,posD};
}