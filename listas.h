#ifndef LISTAS_H
#define LISTAS_H

#include <string>
#include <vector>

typedef struct ListaArtistas ListaArtistas;
typedef struct ListaAlbums ListaAlbums;
typedef struct ListaCanciones ListaCanciones;
typedef struct ListaReproduccion ListaReproduccion;
typedef struct Artista Artista;
typedef struct Album Album;
typedef struct Cancion Cancion;
typedef struct Reproduccion Reproduccion;

struct Artista{
    char *Nombre;
    ListaAlbums *Albums;
    Artista *anterior;
    Artista *siguiente;

    void setArtista(std::string n, ListaAlbums * a, Artista * an, Artista * s);
};

struct Album{
    char *Nombre;
    ListaCanciones *Canciones;
    Album *anterior;
    Album *siguiente;

    void setAlbum(std::string n, ListaCanciones * c, Album * a, Album * s);
};

struct Cancion{
    char *Nombre;
    char *path;
    double rating;
    Cancion *siguiente;

    void setCancion(std::string n, std::string p, double r, Cancion * s);
};

struct Reproduccion{
    Cancion *nodo;
    Album *alb;
    Artista *art;

    Reproduccion *siguiente;
    Reproduccion *anterior;

    void setReproduccion(Cancion *nodo, Reproduccion *s, Reproduccion *a);
};

struct ListaArtistas{
    Artista *cabeza;
    Artista *final;

    void addArtista(Artista *nodo);
    void dibujar();
    Artista * findArtista(std::string nombre);
};

struct ListaAlbums{
    Album *cabeza;
    Album *final;

    void addAlbum(Album * nodo);
    Album * findAlbum(std::string nombre);
};

struct ListaCanciones{
    Cancion *cabeza;
    Cancion *final;

    void addCancion(Cancion * nodo);
    Cancion * findCancion(std::string nombre);
};

struct ListaReproduccion{
    int tipo;
    Reproduccion *cabeza;
    Reproduccion *fin;

    void addCancion(std::string linea, ListaArtistas *biblioteca);
    void dibujar();
    Reproduccion * pop();
};

ListaArtistas * fillListas();
std::vector<std::string> explode(std::string& str, const char& ch);
ListaArtistas * getBiblioteca();
ListaReproduccion * CrearCircular();
ListaReproduccion * CrearPila();
ListaReproduccion * CrearCola();

#endif // LISTAS_H
