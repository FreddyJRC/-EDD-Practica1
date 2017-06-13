#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    crearCircular();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
