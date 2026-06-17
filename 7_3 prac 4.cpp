#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>
template <typename T>
std::vector<T> almacen(typename GrafoP<T>::vertice o, int cantidad, GrafoP<T> &G, std::vector<T> ciudades, std::vector<T>  subvencion, int *coste){
    std::vector<typename GrafoP<T>::vertice> vec2;
    std::vector<T> vec= Dijkstra(G,o,vec2);
    for(size_t i=0; i<vec.size(); i++){
        vec[i]=vec[i]-((vec[i]*subvencion[i])/100);
    }
    int i=0;
    std::vector<T> costes;
    *coste=0;
    while(cantidad>0){
        int minimo=G.INFINITO;
        for(size_t j=0; j<vec.size(); j++){
            if(minimo>vec[j] && vec[j]!=G.INFINITO){
                minimo=vec[j];
                i=j;
            }
        }
        if(cantidad>vec[i]){
            cantidad=cantidad-vec[i];
            coste=coste+vec[i];
            costes[i]=costes[i]+vec[i];
            vec[i]=G.INFINITO;
        }
        else{
            coste=coste+cantidad;
            costes[i]=costes[i]+cantidad;
            
            vec[i]=vec[i]-cantidad;
            cantidad=0;
        }
    }

    return costes;
}