#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <listas.h>
#include <string.h>
#include <vector>

ListaArtistas *biblioteca;
ListaReproduccion *lista;
Reproduccion *playing;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    duracion = 0;
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
    connect(ui->actionBiblioteca, &QAction::triggered, this, &MainWindow::on_MostrarBiblioteca);
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
    //lista->tipo = 0;
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_2->setEnabled(false);

    lista = CrearPila();
    //lista->tipo = 1;
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_2->setEnabled(false);

    lista = CrearCola();
    //lista->tipo = 2;
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
    if(lista->tipo == 0){
        playing = playing->siguiente;
    } else {
        playing = lista->pop();
        ui->label_4->setPixmap(QPixmap("reproduccion.png"));
    }
    if(playing != NULL){
        player->setMedia(QUrl::fromLocalFile(QString::fromStdString(playing->nodo->path)));
        ui->progressBar->setFormat(QString::fromStdString(playing->nodo->Nombre));
        player->play();
    } else {
        ui->progressBar->setFormat("LISTA FINALIZADA");
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

// REPORTES

void MainWindow::on_MostrarBiblioteca()
{
    system("xdg-open biblioteca.png");
}

void MainWindow::on_MostrarTopCanciones()
{
    ListaReproduccion *topCanciones = new ListaReproduccion;
    topCanciones->tipo = 1;
    topCanciones->cabeza = NULL;
    topCanciones->fin = NULL;

    Artista *art = biblioteca->cabeza;

    do{
        Album *alb = art->Albums;

        while (alb != NULL) {
            Cancion *sng = alb->Canciones;

            while (sng != NULL) {
                if(topCanciones->cabeza == NULL){
                    Reproduccion *nuevo = new Reproduccion;
                    nuevo->nodo = sng;
                    nuevo->siguiente = NULL;

                    topCanciones->cabeza = nuevo;
                } else {
                    Reproduccion *actua = topCanciones->cabeza;

                    while (actua != NULL) {
                        if(sng->rating > actua->siguiente->nodo->rating){

                        }
                    }
                }

                sng = sng->siguiente;
            }

            alb = alb->siguiente;
        }

        art = art->siguiente;
    }while(art != biblioteca->cabeza);
}
