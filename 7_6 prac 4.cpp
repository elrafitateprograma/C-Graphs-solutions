#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>

template <typename T>
matriz<T> cambios(GrafoP<T> &G1, GrafoP<T> &G2, int cambio){
    matriz<typename GrafoP<T>::vertice> P1,P2;
    matriz<T> M1=Floyd(G1, P1);
    matriz<T> M2=Floyd(G2, P2);

    std::vector<typename GrafoP<T>::vertice> vec2,vec4,,vec6,vec8;
    std::vector<T> vec=Dijkstra(G1,cambio,vec2);
    std::vector<T> vec3=DijkstraInv(G2,cambio, vec4);

    std::vector<T> vec5=Dijkstra(G2,cambio,vec6);
    std::vector<T> vec7=DijkstraInv(G1,cambio,vec8);

    matriz<T> M3(vec.size());
    matriz<T> M4(vec5.size());
    for (size_t i=0; i<vec3.size(); i++){
        for(size_t j=0; j<vec5.size(); j++){
            if(vec3[i]!=G2.INFINITO && vec[j]!=G1.INFINITO){
                M3[i][j]=vec3[i]+vec[j];
            }
            else{
                M3[i][j]=G1.INFINITO;
            }
            if(vec7[i]!=G1.INFINITO && vec5[j]!=G2.INFINITO){
                M4[i][j]=vec7[i]+vec5[j];
            }
            else{
                M4[i][j]=G2.INFINITO;
            }
        }
    }
    matriz<T> M(vec.size());
    for(size_t i=0; i<vec.size(); i++){
        for (size_t j=0; j<vec.size(); j++){
            M[i][j]=std::min(M1[i][j],std::min(M2[i][j],std::min(M3[i][j],M4[i][j])));
        }
    }
    return M;
}