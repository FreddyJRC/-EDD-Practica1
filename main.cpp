#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
#include <iostream>
#include <listas.h>

ListaArtistas *biblioteca;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    biblioteca = fillListas();
    biblioteca->dibujar();

    return a.exec();
}

ListaArtistas * getBiblioteca(){
    return biblioteca;
}

