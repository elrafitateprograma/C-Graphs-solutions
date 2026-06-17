#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>


float almacen(typename GrafoP<float>::vertice o, GrafoP<float> &G, int cantidad, std::vector<float> capacidad, std::vector<float> subvencion){
    std::vector<typename GrafoP<float>::vertice> vec2;
    std::vector<float> vec= Dijkstra(G,o,vec2);
    float coste=0;

    std::vector<float> cuanto(capacidad.size(), 0.0f);
    for(size_t i=0; i<vec.size(); i++){
        vec[i]=vec[i]- (vec[i] *subvencion[i])/100;
    }
    int y=vec.size();
    while (cantidad>0 && y>0){
        float min=G.INFINITO;
        int pos=0;
        for(size_t i=0; i<vec.size(); i++){
            if(vec[i]!=G.INFINITO){
                if(min>vec[i]){
                    min=vec[i];
                    pos=i;
                }
            }
            
        }
        
        if(cantidad>=capacidad[pos]){
            coste=vec[pos]+coste;
            cuanto[pos]=capacidad[pos];
            
            cantidad=cantidad-capacidad[pos];
            capacidad[pos]=0;
        }
        else{
            cuanto[pos]=cantidad;
            capacidad[pos]=capacidad[pos]-cantidad;
            cantidad =0;
            coste=vec[pos]+coste;
        }
        vec[pos]=G.INFINITO;
        y--;
    }
    return coste;
}