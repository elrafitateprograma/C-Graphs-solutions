#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>
template <typename T>
std::vector<typename GrafoP<T>::vertice> ciudades(GrafoP<T> &G1, GrafoP<T> &G2, int dinero, typename GrafoP<T>::vertice o){
    std::vector<typename GrafoP<T>::vertice> P,P2;
    std::vector<T> vec=Dijkstra(G1,o,P);
    std::vector<T> vec2=Dijkstra(G2,o,P2);

    std::vector<typename GrafoP<T>::vertice> fin;
    for(size_t i=0; i<vec.size(); i++){
        if(vec[i]!=G1.INFINITO || G2.INFINITO!=vec2[i]){
            if(vec[i]!=G1.INFINITO && dinero<=vec[i]){
                fin.push_back(i);
            }
            else if(vec2[i]!=G2.INFINITO && dinero<=vec2[i]){
                fin.push_back(i);
            }
        }
    }
}