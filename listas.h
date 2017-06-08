#ifndef LISTAS_H
#define LISTAS_H

typedef struct ListaArtistas ListaArtistas;
typedef struct ListaAlbums ListaAlbums;
typedef struct ListaCanciones ListaCanciones;
typedef struct Artista Artista;
typedef struct Album Album;
typedef struct Cancion Cancion;

struct Artista{
    char * Nombre;
    ListaAlbums * Albums;
    Artista * anterior;
    Artista * siguiente;

    void setArtista(char * n, ListaAlbums * a, Artista * an, Artista * s){
        Nombre = n;
        Albums = a;
        anterior = an;
        siguiente = s;
    }
};

struct Album{
    char * Nombre;
    ListaCanciones * Canciones;
    Album * anterior;
    Album * siguiente;

    void setAlbum(char * n, ListaCanciones * c, Album * a, Album * s){
        Nombre = n;
        Canciones = c;
        anterior = a;
        siguiente = s;
    }
};

struct Cancion{
    char * Nombre;
    char * path;
    float rating;
    Cancion * siguiente;

    void setCancion(char * n, char * p, float r, Cancion * s){
        Nombre = n;
        path = p;
        rating = r;
        siguiente = s;
    }
};

struct ListaArtistas{
    Artista * cabeza;

    Artista * getLast(){
        Artista * actual = cabeza;

        do {
            actual = actual->siguiente;
        } while (actual != cabeza);

        return actual;
    }
};

struct ListaAlbums{
    Album * cabeza;

    Album * getLast(){
        Album * actual = cabeza;

        while (actual != NULL) {
            actual = actual->siguiente;
        }

        return actual;
    }
};

struct ListaCanciones{
    Cancion * cabeza;

    Cancion * getLast(){
        Cancion * actual = cabeza;

        while (actual != NULL) {
            actual = actual->siguiente;
        }

        return actual;
    }
};

#endif // LISTAS_H
