#include <listas.h>

void Artista::setArtista(char * n, ListaAlbums * a, Artista * an, Artista * s){
    Nombre = n;
    Albums = a;
    anterior = an;
    siguiente = s;
}

void Album::setAlbum(char * n, ListaCanciones * c, Album * a, Album * s){
    Nombre = n;
    Canciones = c;
    anterior = a;
    siguiente = s;
}

void Cancion::setCancion(char * n, char * p, float r, Cancion * s){
    Nombre = n;
    path = p;
    rating = r;
    siguiente = s;
}

Artista * ListaArtistas::getLast(){
    Artista * actual = cabeza;

    do {
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
