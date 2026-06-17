#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>

int trasporte(GrafoP<int> &G1, GrafoP<int> &G2, GrafoP<int> &G3, int cambiobustren, int cambioaero, typename GrafoP<int>::vertice o, typename GrafoP<int>::vertice d){
    GrafoP<int> G(G1.numVert()*3);
    for(size_t i=0; i<G1.numVert(); i++){
        for(size_t j=0; j<G1.numVert(); j++){
            G[i][j]=G1[i][j];
        }
    }
    for(size_t i=G1.numVert(); i<G1.numVert()+G2.numVert(); i++){
        for(size_t j=G1.numVert(); j<G1.numVert()+G2.numVert(); j++){
            G[i][j]=G2[i-G1.numVert()][j-G1.numVert()];
        }
    }

    for(size_t i=G1.numVert()+G2.numVert(); i<G.numVert(); i++){
        for(size_t j=G1.numVert()+G2.numVert(); j<G.numVert(); j++){
            G[i][j]=G3[i-G1.numVert()-G2.numVert()][j-G1.numVert()-G2.numVert()];
        }
    }


    for(size_t i=0; i<G1.numVert(); i++){
        G[i][i+G1.numVert()]=cambiobustren;
        G[G1.numVert()+i][i]=cambiobustren;
    }

    for(size_t i=0; i<G1.numVert(); i++){
        G[i][i+G1.numVert()+G2.numVert()]=cambioaero;
        G[i+G1.numVert()+G2.numVert()][i]=cambioaero;
    }

    for(size_t i=G1.numVert(); i<G1.numVert()+G2.numVert(); i++){
        G[i][i+G2.numVert()]=cambioaero;
        G[i+G2.numVert()][i]=cambioaero;
    }

    std::vector<GrafoP<int>::vertice> vec2,vec4,vec6;
    std::vector<int> vec,vec3,vec5;
    vec=Dijkstra(G,o,vec2);
    vec3=Dijkstra(G,o+G1.numVert(),vec4);
    vec5=Dijkstra(G,o+G1.numVert()+G2.numVert(),vec6);

    int total1=std::min(vec[d], std::min(vec[d+G1.numVert()],vec[d+G1.numVert()+G2.numVert()]));
    int total2=std::min(vec3[d], std::min(vec3[d+G1.numVert()],vec3[d+G1.numVert()+G2.numVert()]));
    int total3=std::min(vec5[d], std::min(vec5[d+G1.numVert()],vec5[d+G1.numVert()+G2.numVert()]));

    return (std::min(total1, std::min(total2,total3)));
}