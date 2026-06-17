#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>
int funcion(GrafoP<int> &G1, GrafoP<int> &G2, typename GrafoP<int>::vertice o, typename GrafoP<int>::vertice d){
    std::vector<GrafoP<int>::vertice> vec2,vec4,vec6,vec8;
    std::vector<int> vec,vec3,vec5,vec7;
    vec=Dijkstra(G1,o,vec2);
    vec3=Dijkstra(G2,o,vec4);
    vec5=DijkstraInv(G1,d,vec6);
    vec7=DijkstraInv(G2,d,vec8);

    int total=G1.INFINITO;
    for(size_t i=0; i<vec.size(); i++){
        if(vec[i]!=G1.INFINITO && vec7[i]!=G2.INFINITO){
            int cost=vec[i]+vec7[i];
            total=std::min(total,cost);
        }

        if(vec3[i]!=G2.INFINITO && vec5[i]!=G1.INFINITO){
            int cost=vec3[i]+vec5[i];
            total=std::min(total,cost);
        }
    }
    return total;
}