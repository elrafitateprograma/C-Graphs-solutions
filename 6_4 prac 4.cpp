#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>
template <typename T>
void modificar(GrafoP<T> &G, std::vector<typename GrafoP<T>::vertice> ciudades, std::vector<std::pair<typename GrafoP<T>::vertice, typename GrafoP<T>::vertice>> carretera){
    for(size_t i=0; i<G.numVert(); i++){
        for (size_t j=0; j<ciudades.size(); j++){
            G[i][ciudades[j]]=G.INFINITO;
            G[ciudades[j]][i]=G.INFINITO;
        }
    }

    for(size_t i=0; i<carretera.size(); i++){
        G[carretera[i].first][carretera[i].second]=G.INFINITO;
    }
}

template <typename T>
matriz<T> zuelandia(GrafoP<T> &G, std::vector<typename GrafoP<T>::vertice> ciudades, std::vector<std::pair<typename GrafoP<T>::vertice, typename GrafoP<T>::vertice>> carretera, int capital){
    modificar(G, ciudades, carretera);
    std::vector<typename GrafoP<T>::vertice> vec2,vec4;
    std::vector<T> vec=Dijkstra(G,capital,vec2);
    std::vector<T> vec3=DijkstraInv(G,capital, vec4);
    matriz<T> M(G.numVert());
    for(size_t i=0; i<G.numVert; i++){
        for(size_t j=0; j<G.numVert(); j++){
            if(vec[i]== G.INFINITO || vec3[j]==G.INFINITO){
                M[i][j]=G.INFINITO;
            }
            else if(i==j && vec[i]!= G.INFINITO && vec3[j]!=G.INFINITO){
                M[i][j]=0;
            }
            else{
                M[i][j]=vec[i]+vec3[j];
            }
            
        }
    }
    return M;
}