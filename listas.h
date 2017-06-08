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

    void setArtista(char * n, ListaAlbums * a, Artista * an, Artista * s);
};

struct Album{
    char * Nombre;
    ListaCanciones * Canciones;
    Album * anterior;
    Album * siguiente;

    void setAlbum(char * n, ListaCanciones * c, Album * a, Album * s);
};

struct Cancion{
    char * Nombre;
    char * path;
    float rating;
    Cancion * siguiente;

    void setCancion(char * n, char * p, float r, Cancion * s);
};

struct ListaArtistas{
    Artista * cabeza;

    Artista * getLast();
};

struct ListaAlbums{
    Album * cabeza;

    Album * getLast();
};

struct ListaCanciones{
    Cancion * cabeza;

    Cancion * getLast();
};

#endif // LISTAS_H
