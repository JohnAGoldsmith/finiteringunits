#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cprimecanvas.h"

namespace Ui {
class MainWindow;
}

class cPrimeCanvas;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    cPrimeCanvas *primeCanvas;
};

#endif // MAINWINDOW_H
