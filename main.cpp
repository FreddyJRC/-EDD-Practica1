#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
#include <iostream>
#include <listas.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    char s = 'c';
    char * a2 = &s;
    Artista* nuevo = (Artista*)malloc(sizeof(Artista));
    nuevo->setArtista(a2, NULL, NULL, NULL);

    std::cout << *nuevo->Nombre << std::endl;

    return a.exec();
}
