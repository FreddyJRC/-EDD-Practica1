#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <listas.h>

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
    ListaReproduccion *lista = crearCircular();
}
