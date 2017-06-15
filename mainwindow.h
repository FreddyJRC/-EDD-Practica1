#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_positionChanged(qint64 posicion);

    void on_durationChanged(qint64 posicion);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_MostrarBiblioteca();

    void on_MostrarTopCanciones();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
};

#endif // MAINWINDOW_H
