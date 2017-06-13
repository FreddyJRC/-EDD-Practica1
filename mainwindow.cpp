#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <listas.h>

ListaArtistas *biblioteca;
ListaReproduccion *lista;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->setEnabled(true);
    ui->pushButton_8->setEnabled(true);

    lista = CrearCircular();
}

void MainWindow::on_pushButton_8_clicked()
{
    QString song = ui->lineEdit->text();
    biblioteca = getBiblioteca();
    if(song.length() > 0){
        lista->addCancion(song.toStdString(), biblioteca);
    }

}
