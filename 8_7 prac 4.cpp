#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>

struct coordenada
{
    int x,y;
};


float heuclidea(coordenada a, coordenada b){
    return (sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)));
}


float reconstruccion(std::vector<coordenada> Deimos, std::vector<coordenada> Fobos, std::vector<typename GrafoP<int>::vertice> Fcos,
std::vector<typename GrafoP<int>::vertice> Dcos, typename GrafoP<int>::vertice o, typename GrafoP<int>::vertice d){
    GrafoP<float> G(Deimos.size()+Fobos.size());
    float max=0;
    for (size_t i=0; i<Deimos.size(); i++){
        for (size_t j=0; j<Deimos.size(); j++){
            if(i!=j){
                G[i][j]=heuclidea(Deimos[i],Deimos[j]);
                if(G[i][j]!=G.INFINITO && max<G[i][j]){
                    max=G[i][j];
                }
            }
            else{
                G[i][j]=0;
            }
        }
    }

    for (size_t i=Deimos.size(); i<G.numVert(); i++){
        for (size_t j=Deimos.size(); j<G.numVert(); j++){
            if(i!=j){
                G[i][j]=heuclidea(Fobos[i-Deimos.size()],Fobos[j-Deimos.size()]);
                if(G[i][j]!=G.INFINITO && max<G[i][j]){
                    max=G[i][j];
                }
            }
            else{
                G[i][j]=0;
            }
        }
    }

    for(size_t i=0; i<Dcos.size(); i++){
        for(size_t j=0; j<Fcos.size();j++){
            G[Dcos[i]][Fcos[j]+Dcos.size()]=heuclidea(Deimos[Dcos[i]], Fobos[Fcos[j]]) +max;
            G[Fcos[j]+Dcos.size()][Dcos[i]]=heuclidea(Fobos[Fcos[j]], Deimos[Dcos[i]]) +max;
        }
    }

    G=Kruskall(G);
    for(size_t i=0; i<Dcos.size(); i++){
        for(size_t j=0; j<Fcos.size();j++){
            if(G[Dcos[i]][Fcos[j]+Dcos.size()] != G.INFINITO && G[Fcos[j]+Dcos.size()][Dcos[i]]!=G.INFINITO)
            G[Dcos[i]][Fcos[j]+Dcos.size()]-= max;
            G[Fcos[j]+Dcos.size()][Dcos[i]]-= max;
        }
    }

    std::vector<typename GrafoP<float>::vertice> P;
    std::vector<float> vec=Dijkstra(G,o,P);
    return vec[d];

}