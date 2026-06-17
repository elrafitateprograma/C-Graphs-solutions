#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <map>
#include "particion.h"
#include "particion.cpp"
#include "apo.h"
struct coordenadas
{
    GrafoP<int>::vertice x,y;
    coordenadas(GrafoP<int>::vertice a, GrafoP<int>::vertice b): x(a),y(b){}
    bool operator ==(const coordenadas& ciu) const{
        return this->x==ciu.x && this->y==ciu.y;
    }

    bool operator<(const coordenadas& other) const {
    return x < other.x || (x == other.x && y < other.y);
}

};
struct linea_aerea{
    coordenadas o,d;
    float coste;
    linea_aerea(coordenadas a, coordenadas b):o(a),d(b), coste(distancia(a,b)){}

    bool operator<(const linea_aerea& a) const{
        return this->coste<a.coste;
    }
};



double distancia(const coordenadas& a, const coordenadas& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

std::vector<linea_aerea> aeropuerto(std::vector<coordenadas> lista, Grafo a){
    Apo<linea_aerea> A(a.numVert() * (a.numVert() - 1)/2);
    Particion P(a.numVert());
    for(size_t i=0; i< a.numVert(); i++){
        for (size_t j=0; j<a.numVert(); j++){
            if(a[i][j]){
                if(P.encontrar(i)!= P.encontrar(j)){
                    P.unir(P.encontrar(i),P.encontrar(j));
                }
            }
        }
    }
    std::vector<int> islas;
    int rep;
    for(size_t i=0; i<a.numVert(); i++){
        rep=P.encontrar(i);
        if(islas.empty()){
            islas.push_back(rep);
        }
        else{
            size_t j=0;
            while (j<islas.size() && rep!=islas[j]){
                j++;
            }
            if(j==islas.size()){
                islas.push_back(rep);
            }
        }
    }

    for(size_t i=0; i<a.numVert(); i++){
        for(size_t j=i+1; j<a.numVert(); j++){
            if(P.encontrar(i)!=P.encontrar(j) ){
                linea_aerea aux(lista[i], lista[j]);
                A.insertar(aux);

            }
        }
    }
    /*
    std::map<int, std::vector<coordenadas>> islas;
    for(size_t i =0; i<lista.size(); i++){
        int representante=P.encontrar(i);
        islas[representante].push_back(lista[i]);
    }*/
    std::map<coordenadas, int> ciu_islas;
    for(size_t i =0; i<lista.size(); i++){
        int representante=P.encontrar(i);
        ciu_islas[lista[i]]= representante;
    }
    

    matriz<bool> prueba(islas.size(),false);
    std::vector<linea_aerea> sol;
    size_t i=0;
    while(!A.vacio() && i<a.numVert()*(a.numVert()-1)/2){
        linea_aerea aux= A.cima();
        size_t j=0, pos1=ciu_islas[aux.o], pos2=ciu_islas[aux.d];
        size_t isla1,isla2;
        while(j<islas.size()){
            if(pos1==islas[j]){
                isla1=j;
            }
            if(pos2==islas[j]){
                isla2=j;
            }

            j++;
        }
        
        /*
        for(j =0; j<lista.size(); j++){
            if(aux.o==lista[j]){
                pos1=j;
            }
            if(aux.d==lista[j]){
                pos2=j;
            }
        }*/
        if(pos1!=pos2 && !prueba[isla1][isla2]){
            prueba[isla1][isla2]=true;
            prueba[isla2][isla1]=true;
            A.suprimir();
            sol.push_back(aux);
        }
        
    }

    return sol;

}


