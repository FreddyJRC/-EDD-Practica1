#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <listas.h>

void fillListas(){

    std::ifstream file("../res/ListaReproduccion.txt");
    std::vector<std::string> segmentos;
    std::string line;

    ListaArtistas * artistas = (ListaArtistas*) malloc(sizeof(ListaArtistas));
    artistas->cabeza = NULL;

    while (std::getline(file, line, '\n')){
        line.pop_back();
        segmentos = explode(line, '_');

        artistas->findArtista(segmentos[0]);
    }

}

//Constructores para los Nodos.
void Artista::setArtista(std::string n, ListaAlbums * a, Artista * an, Artista * s){
    Nombre = n;
    Albums = a;
    anterior = an;
    siguiente = s;
}

void Album::setAlbum(std::string n, ListaCanciones * c, Album * a, Album * s){
    Nombre = n;
    Canciones = c;
    anterior = a;
    siguiente = s;
}

void Cancion::setCancion(std::string n, std::string p, float r, Cancion * s){
    Nombre = n;
    path = p;
    rating = r;
    siguiente = s;
}

//Metodos para agregar nodos a las listas.

void ListaArtistas::addArtista(Artista *nodo){
    if(this->cabeza == NULL){

        cabeza = nodo;
        nodo->siguiente = nodo;
        nodo->anterior = nodo;

    } else {

        Artista * last = this->getLast();

        last->siguiente = nodo;

        nodo->anterior = last;
        nodo->siguiente = this->cabeza;

    }
}

void ListaAlbums::addAlbum(Album *nodo){
    if(cabeza == NULL){

        cabeza = nodo;
        nodo->siguiente = NULL;
        nodo->anterior = NULL;

    } else {

        Album * last = this->getLast();

        last->siguiente = nodo;

        nodo->anterior = last;
        nodo->siguiente = NULL;

    }
}

void ListaCanciones::addCancion(Cancion *nodo){
    if(cabeza == NULL){

        cabeza = nodo;
        nodo->siguiente = NULL;

    } else {

        Cancion * last = this->getLast();

        last->siguiente = nodo;
        nodo->siguiente = NULL;

    }
}

//busqueda de elementos

Artista * ListaArtistas::findArtista(std::string nombre){
    Artista *actual = cabeza;
    bool found = false;

    if(actual == NULL){
        Artista * nuevo = (Artista*) malloc(sizeof(Artista));
        nuevo->setArtista(nombre, NULL, NULL, NULL);
        addArtista(nuevo);
        actual = nuevo;
        free(nuevo);
    }else {
        do {
            if(actual->Nombre.compare(nombre) == 0){
                found = true;
                break;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        if(!found){
            Artista * nuevo = (Artista*) malloc(sizeof(Artista));
            nuevo->setArtista(nombre, NULL, NULL, NULL);
            addArtista(nuevo);
            actual = nuevo;
            free(nuevo);
        }
    }

    return actual;
}

//Metodos auxiliares

Artista * ListaArtistas::getLast(){
    Artista *actual = cabeza;

    //if(actual != NULL){
        do {
            //std::cout << actual->Nombre << std::endl;
            actual = actual->siguiente;
        } while (actual != cabeza);

    return actual;
}

Album * ListaAlbums::getLast(){
    Album * actual = cabeza;

        while (actual != NULL) {
            actual = actual->siguiente;
        }

    return actual;
}

Cancion * ListaCanciones::getLast(){
    Cancion * actual = cabeza;

        while (actual != NULL) {
            actual = actual->siguiente;
        }

    return actual;
}

std::vector<std::string> explode(std::string& str, const char& ch) {
    std::string next;
    std::vector<std::string> result;

    // For each character in the string
    for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
            if (!next.empty()) {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if (!next.empty())
         result.push_back(next);
    return result;
}
