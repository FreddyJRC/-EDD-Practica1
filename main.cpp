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

    ListaArtistas *biblioteca = fillListas();
    biblioteca->dibujar();

    return a.exec();
}

