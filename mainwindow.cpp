#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <listas.h>
#include <string.h>

ListaArtistas *biblioteca;
ListaReproduccion *lista;
Reproduccion *playing;
qint64 duracion;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    duracion = 0;
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);

    lista = CrearCircular();
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_2->setEnabled(false);

    lista = CrearPila();
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_2->setEnabled(false);

    lista = CrearCola();
}

void MainWindow::on_pushButton_8_clicked()
{
    QString song = ui->lineEdit->text();
    biblioteca = getBiblioteca();
    if(song.length() > 0){
        lista->addCancion(song.toStdString(), biblioteca);
        playing = lista->cabeza;
        player->setMedia(QUrl::fromLocalFile(QString::fromStdString(playing->nodo->path)));
        ui->progressBar->setFormat(QString::fromStdString(playing->nodo->Nombre));

        ui->label_4->setPixmap(QPixmap("reproduccion.png"));
        ui->label_4->setScaledContents( true );
        ui->label_4->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
    ui->lineEdit->setText("");
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton_4->setEnabled(true);
    ui->pushButton->setEnabled(false);
    player->play();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_4->setEnabled(false);
    player->stop();
}

void MainWindow::on_durationChanged(qint64 posicion)
{
    ui->progressBar->setMaximum(posicion);
}

void MainWindow::on_positionChanged(qint64 posicion)
{
    ui->progressBar->setValue(posicion);
}

void MainWindow::on_pushButton_3_clicked()
{
    player->stop();
    if(lista->tipo == 1){
        playing = playing->siguiente;
    } else {
        playing = lista->pop();
        ui->label_4->setPixmap(QPixmap("reproduccion.png"));
    }
    if(playing != NULL){
        player->setMedia(QUrl::fromLocalFile(QString::fromStdString(playing->nodo->path)));
        ui->progressBar->setFormat(QString::fromStdString(playing->nodo->Nombre));
        player->play();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    player->stop();
    playing = playing->anterior;
    player->setMedia(QUrl::fromLocalFile(QString::fromStdString(playing->nodo->path)));
    ui->progressBar->setFormat(QString::fromStdString(playing->nodo->Nombre));
    player->play();
}
