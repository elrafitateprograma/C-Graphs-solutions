#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>
struct puente
{
    typename GrafoP<int>::vertice x,y;
    puente(int a, int b): x(a), y(b){}
};


template <typename T>
std::vector<puente> islas(GrafoP<T>& G1, GrafoP<T>& G2, GrafoP<T>& G3, std::vector<typename GrafoP<int>::vertice> cos1, 
std::vector<typename GrafoP<int>::vertice> cos2, std::vector<typename GrafoP<int>::vertice> cos3){
    matriz<typename GrafoP<T>::vertice> P1,P2,P3;
    matriz<T> M1=Floyd(G1,P1);
    matriz<T> M2 = Floyd(G2,P2);
    matriz<T> M3 = Floyd(G3,P3);
    std::vector<puente> p;
    T min1=G1.INFINITO;
    int pos1;
    for(size_t i=0; i<cos1.size(); i++){
        T coste=0;
        for(size_t j=0; j<G1.numVert(); j++){
            if(M1[cos1[i]][j]!= G1.INFINITO && i!=j){
                coste=coste+M1[cos1[i]][j];
                
            }
        }
        if(min1>coste){
            min1=coste;
            pos1=i;
        }

    }

    T min2=G2.INFINITO;
    int pos2;
    for(size_t i=0; i<cos2.size(); i++){
        T coste=0;
        for(size_t j=0; j<G2.numVert(); j++){
            if(M2[cos2[i]][j]!= G2.INFINITO && i!=j){
                coste=coste+M2[cos2[i]][j];
                
            }
        }
        if(min2>coste){
            min2=coste;
            pos2=i;
        }

    }

    T min3=G3.INFINITO;
    int pos3;
    for(size_t i=0; i<cos3.size(); i++){
        T coste=0;
        for(size_t j=0; j<G3.numVert(); j++){
            if(M3[cos3[i]][j]!= G3.INFINITO && i!=j){
                coste=coste+M3[cos3[i]][j];
                
            }
        }
        if(min3>coste){
            min3=coste;
            pos3=i;
        }

    }

    p.push_back(puente(pos1,pos2));
    p.push_back(puente(pos2,pos3));
    return p;

}