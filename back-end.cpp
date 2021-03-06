#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <listas.h>

ListaArtistas *artistas;

ListaArtistas * fillListas(){

    std::ifstream file("../res/ListaReproduccion.txt");
    std::vector<std::string> segmentos;
    std::string line;

    artistas = (ListaArtistas*) malloc(sizeof(ListaArtistas));
    artistas->cabeza = NULL;
    artistas->final = NULL;

    while (std::getline(file, line, '\n')){
        line.pop_back();
        segmentos = explode(line, '_');

        Artista *ArtistaActual = artistas->findArtista(segmentos[0]);

        if(ArtistaActual->Albums == NULL){
            ListaAlbums *albums = (ListaAlbums*) malloc(sizeof(ListaAlbums));
            albums->cabeza = NULL;
            albums->final = NULL;
            ArtistaActual->Albums = albums;
        }

        Album *AlbumActual = ArtistaActual->Albums->findAlbum(segmentos[1]);

        if(AlbumActual->Canciones == NULL){
            ListaCanciones *canciones = (ListaCanciones*) malloc(sizeof(ListaCanciones));
            canciones->cabeza = NULL;
            canciones->final = NULL;
            AlbumActual->Canciones = canciones;
        }

        Cancion *CancionActual = (Cancion*) malloc(sizeof(Cancion));
        CancionActual->setCancion(segmentos[2], segmentos[3], std::stof(segmentos[4].c_str()), NULL);
        AlbumActual->Canciones->addCancion(CancionActual);

    }

    return artistas;
}

ListaReproduccion * CrearCircular(){
    ListaReproduccion *circular = (ListaReproduccion*) malloc(sizeof(ListaReproduccion));
    circular->tipo = 0;
    circular->cabeza = NULL;
    circular->fin = NULL;

    return circular;
}

ListaReproduccion * CrearPila(){
    ListaReproduccion *pila = (ListaReproduccion*) malloc(sizeof(ListaReproduccion));
    pila->tipo = 1;
    pila->cabeza = NULL;
    pila->fin = NULL;

    return pila;
}

ListaReproduccion * CrearCola(){
    ListaReproduccion *cola = (ListaReproduccion*) malloc(sizeof(ListaReproduccion));
    cola->tipo = 2;
    cola->cabeza = NULL;
    cola->fin = NULL;

    return cola;
}

//Constructores para los Nodos.
void Artista::setArtista(std::string n, ListaAlbums * a, Artista * an, Artista * s){
    char *cstr = new char[n.length() + 1];
    std::strcpy(cstr, n.c_str());

    Nombre = cstr;
    Albums = a;
    anterior = an;
    siguiente = s;
}

void Album::setAlbum(std::string n, ListaCanciones * c, Album * a, Album * s){
    char *cstr = new char[n.length() + 1];
    std::strcpy(cstr, n.c_str());

    Nombre = cstr;
    Canciones = c;
    anterior = a;
    siguiente = s;
}

void Cancion::setCancion(std::string n, std::string p, double r, Cancion * s){
    char *cstr = new char[n.length() + 1];
    std::strcpy(cstr, n.c_str());

    char *cstr2 = new char[p.length() + 1];
    std::strcpy(cstr2, p.c_str());

    Nombre = cstr;
    path = cstr2;
    rating = r;
    siguiente = s;
}

void Reproduccion::setReproduccion(Cancion *nodo, Reproduccion *s, Reproduccion *a){
    this->nodo = nodo;
    this->siguiente = s;
    this->anterior = a;
}

//Metodos para agregar nodos a las listas.

void ListaArtistas::addArtista(Artista *nodo){
    if(this->cabeza == NULL){

        cabeza = nodo;
        final = nodo;
        nodo->siguiente = nodo;
        nodo->anterior = nodo;

    } else {

        nodo->siguiente = this->final->siguiente;
        nodo->anterior = this->final;
        this->cabeza->anterior = nodo;
        this->final->siguiente = nodo;
        this->final = nodo;

    }
}

void ListaAlbums::addAlbum(Album *nodo){
    if(cabeza == NULL){

        cabeza = nodo;
        final = nodo;
        nodo->siguiente = NULL;
        nodo->anterior = NULL;

    } else {

        final->siguiente = nodo;
        nodo->anterior = final;
        nodo->siguiente = NULL;
        this->final = nodo;

    }
}

void ListaCanciones::addCancion(Cancion *nodo){
    if(cabeza == NULL){

        cabeza = nodo;
        final = nodo;
        nodo->siguiente = NULL;

    } else {

        final->siguiente = nodo;
        nodo->siguiente = NULL;
        this->final = nodo;

    }
}

void ListaReproduccion::addCancion(std::string linea, ListaArtistas *biblioteca){
    std::vector<std::string> segmentos = explode(linea, '_');

    Artista *art = biblioteca->findArtista(segmentos[0]);
    Album *alb = art->Albums->findAlbum(segmentos[1]);
    Cancion *sng = alb->Canciones->findCancion(segmentos[2]);
    Reproduccion *nuevo = (Reproduccion*) malloc(sizeof(Reproduccion));

    if(this->tipo == 0){ //circular

        if(this->cabeza ==  NULL){
            nuevo->setReproduccion(sng, nuevo, nuevo);
            this->cabeza = this->fin = nuevo;
        } else {
            nuevo->setReproduccion(sng, cabeza, fin);
            fin->siguiente = nuevo;
            cabeza->anterior = nuevo;
            fin = nuevo;
        }

    } else if (this->tipo == 1) { //pila

        if(this->cabeza == NULL){
            nuevo->setReproduccion(sng, NULL, NULL);
            this->cabeza = this->fin = nuevo;
        }else{
            nuevo->setReproduccion(sng, cabeza, NULL);
            this->cabeza = nuevo;
        }

    } else if (this->tipo == 2){ //cola

        if(this->cabeza == NULL){
            nuevo->setReproduccion(sng, NULL, NULL);
            this->cabeza = this->fin = nuevo;
        } else {
            nuevo->setReproduccion(sng, NULL, NULL);
            this->fin->siguiente = nuevo;
            this->fin = nuevo;
        }

    }

    this->dibujar();
}

//busqueda de elementos

Artista * ListaArtistas::findArtista(std::string nombre){
    Artista *actual = this->cabeza;
    bool found = false;

    if(actual == NULL){
        Artista *nuevo = (Artista*) malloc(sizeof(Artista));
        nuevo->setArtista(nombre, NULL, NULL, NULL);
        addArtista(nuevo);
        return nuevo;
    } else {
        do {
            std::string s(actual->Nombre);
            if(s.compare(nombre) == 0){
                found = true;
                break;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        if(!found){
            Artista *nuevoArtista = (Artista*) malloc(sizeof(Artista));
            nuevoArtista->setArtista(nombre, NULL, NULL, NULL);
            this->addArtista(nuevoArtista);
            return nuevoArtista;
        }
    }

    return actual;
}

Album * ListaAlbums::findAlbum(std::string nombre){
    Album *actual = this->cabeza;
    bool found = false;

    if(actual == NULL){
        Album *nuevo = (Album*) malloc(sizeof(Album));
        nuevo->setAlbum(nombre, NULL, NULL, NULL);
        addAlbum(nuevo);
        return nuevo;
    } else {
        while (actual != NULL) {
            std::string s(actual->Nombre);
            if(s.compare(nombre) == 0){
                found = true;
                break;
            }
            actual = actual->siguiente;
        }

        if(!found){
            Album *nuevo = (Album*) malloc(sizeof(Album));
            nuevo->setAlbum(nombre, NULL, NULL, NULL);
            this->addAlbum(nuevo);
            return nuevo;
        }
    }

    return actual;
}

Cancion * ListaCanciones::findCancion(std::string nombre){
    Cancion *actual = this->cabeza;
    bool found = false;

    if(actual == NULL){
        Cancion *nuevo = (Cancion*) malloc(sizeof(Cancion));
        nuevo->setCancion(nombre, NULL, 0, NULL);
        addCancion(nuevo);
        return nuevo;
    } else {
        while (actual != NULL) {
            std::string s(actual->Nombre);
            if(s.compare(nombre) == 0){
                found = true;
                break;
            }
            actual = actual->siguiente;
        }

        if(!found){
            Cancion *nuevo = (Cancion*) malloc(sizeof(Cancion));
            nuevo->setCancion(nombre, NULL, 0, NULL);
            this->addCancion(nuevo);
            return nuevo;
        }
    }

    return actual;
}

Reproduccion * ListaReproduccion::pop(){
    Reproduccion *tmp;

    tmp = this->cabeza;
    if(tmp != NULL){
        cabeza = cabeza->siguiente;
        tmp->siguiente = NULL;
        this->dibujar();
    }

    return tmp;
}

//Metodos auxiliares

ListaArtistas * getBiblioteca(){
    return artistas;
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

void ListaArtistas::dibujar(){
    FILE *fs = NULL;
    fs = fopen("biblioteca.dot", "w+");

    int i = 0, j = 0;
    Artista *actual = this->cabeza;

    fprintf(fs, "digraph G {\n {rank=same;");
    do{
        fprintf(fs, "\"%s\"; ", actual->Nombre);
        actual = actual->siguiente;
    }while(actual != this->cabeza);
    fprintf(fs, "}\n");
    actual = this->cabeza;

    do{
        fprintf(fs, "\"%s\" -> \"%s\" [dir=both];\n", actual->Nombre, actual->siguiente->Nombre);

        Album *AlbumActual = actual->Albums->cabeza;
        fprintf(fs, "\"%s\" -> \"%s\";\n", actual->Nombre, AlbumActual->Nombre);
        fprintf(fs, "subgraph cluster%d {\n rank=same;\n", i);

        while (AlbumActual != NULL) {
            if(AlbumActual->siguiente == NULL){
                fprintf(fs, "\"%s\";\n", AlbumActual->Nombre);
            } else {
                fprintf(fs, "\"%s\" -> \"%s\" [dir=both];\n", AlbumActual->Nombre, AlbumActual->siguiente->Nombre);
            }

            Cancion *CancionActual = AlbumActual->Canciones->cabeza;
            fprintf(fs, "\"%s\" -> \"%s\";\n", AlbumActual->Nombre, CancionActual->Nombre);
            fprintf(fs, "subgraph cluster%d_%d {\n rank=same;\n", i, j);

            while (CancionActual != NULL) {
                if(CancionActual->siguiente == NULL){
                    fprintf(fs, "\"%s\";\n", CancionActual->Nombre);
                } else {
                    fprintf(fs, "\"%s\" -> \"%s\";\n", CancionActual->Nombre, CancionActual->siguiente->Nombre);
                }
                CancionActual = CancionActual->siguiente;
            }

            fprintf(fs, "}\n");
            ++j;

            AlbumActual = AlbumActual->siguiente;
        }

        fprintf(fs, "}\n");
        j = 0;
        ++i;

        actual = actual->siguiente;
    }while (actual != this->cabeza);
    fprintf(fs, "}");
    fclose(fs);

    system("dot -Tpng biblioteca.dot -o biblioteca.png");
}

void ListaReproduccion::dibujar(){
    FILE *fs = NULL;
    fs = fopen("reproduccion.dot", "w+");

    Reproduccion *actual = this->cabeza;

    fprintf(fs, "digraph G {\n rank=same;\n");
    fprintf(fs, "\"%s\"", actual->nodo->Nombre);
    actual = actual->siguiente;
    if(this->tipo == 0){
        while(actual != this->cabeza){
            fprintf(fs, " -> \"%s\"", actual->nodo->Nombre);
            actual = actual->siguiente;
        }
        fprintf(fs, " -> \"%s\" [dir=both]", this->cabeza->nodo->Nombre);
    } else {
        while (actual != NULL) {
            fprintf(fs, " -> \"%s\"", actual->nodo->Nombre);
            actual = actual->siguiente;
        }
    }
    fprintf(fs, ";\n }");
    fclose(fs);

    system("dot -Tpng reproduccion.dot -o reproduccion.png");
}
