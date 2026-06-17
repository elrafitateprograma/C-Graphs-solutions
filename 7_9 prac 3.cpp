#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>

int taxis(GrafoP<int> &G1, GrafoP<int> &G2, typename GrafoP<int>::vertice o, typename GrafoP<int>::vertice d, int cambio){
    GrafoP<int> G(G1.numVert() + G2.numVert());
    for(size_t i=0; i<G1.numVert(); i++){
        for (size_t j=0; j< G1.numVert(); j++){
            G[i][j]=G1[i][j];
        }
    }
    for(size_t i=G1.numVert(); i<G.numVert(); i++){
        for (size_t j=G1.numVert(); j< G.numVert(); j++){
            G[i][j]=G2[i][j];
        }
    }

    for(size_t i=0; i<G1.numVert(); i++){
        G[i][i+G1.numVert()]=cambio;
        G[i+G1.numVert()][i]=cambio;
    }

    std::vector<GrafoP<int>::vertice> vec2,vec4;
    std::vector<int> vec,vec3;
    vec=Dijkstra(G,o,vec2);
    vec3=Dijkstra(G,o+G1.numVert(),vec4);
    int total=std::min(vec[d],std::min(vec3[d],std::min(vec[d+G1.numVert()],vec3[d+G1.numVert()])));

    return total;
}