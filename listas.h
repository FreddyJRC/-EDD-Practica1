#ifndef LISTAS_H
#define LISTAS_H

#include <string>
#include <vector>

typedef struct ListaArtistas ListaArtistas;
typedef struct ListaAlbums ListaAlbums;
typedef struct ListaCanciones ListaCanciones;
typedef struct Artista Artista;
typedef struct Album Album;
typedef struct Cancion Cancion;

struct Artista{
    std::string Nombre;
    ListaAlbums *Albums;
    Artista *anterior;
    Artista *siguiente;

    void setArtista(std::string n, ListaAlbums * a, Artista * an, Artista * s);
};

struct Album{
    std::string Nombre;
    ListaCanciones *Canciones;
    Album *anterior;
    Album *siguiente;

    void setAlbum(std::string n, ListaCanciones * c, Album * a, Album * s);
};

struct Cancion{
    std::string Nombre;
    std::string path;
    float rating;
    Cancion *siguiente;

    void setCancion(std::string n, std::string p, float r, Cancion * s);
};

struct ListaArtistas{
    Artista *cabeza;

    void addArtista(Artista *nodo);
    Artista * findArtista(std::string nombre);
    Artista * getLast();
};

struct ListaAlbums{
    Album *cabeza;

    void addAlbum(Album * nodo);
    Album * getLast();
};

struct ListaCanciones{
    Cancion *cabeza;

    void addCancion(Cancion * nodo);
    Cancion * getLast();
};

void fillListas();
std::vector<std::string> explode(std::string& str, const char& ch);
#endif // LISTAS_H
