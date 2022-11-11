#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include "cprimecanvas.h"

class cDotPage;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     QList<cDotPage*>*  getDotPageCollection() {return &DotPageCollection;}
     int  get_UI_base() {return QLedit1->text().toInt();}
     void set_UI_base(int newbase);
     void increment_UI_base(int n = 1);

     void        compute_primes_and_factors(int upto_N);
     QList<int> * get_factors(int n) {return m_factors[n]; }
     int         get_largest_integer_factored();
     int         get_largest_prime() {return m_primes.back();}
private:

    cPrimeCanvas *      m_primeCanvas;
    QList<cDotPage*> DotPageCollection;
    void createMenu();
    void createHorizontalGroupBox();
    void createGridGroupBox();
    void createFormGroupBox();
        enum { NumGridRows = 3  };
    void initialize_prime_numbers();
        QMenuBar *menuBar;
        QGroupBox   *m_horizontalGroupBox;
        QGroupBox *gridGroupBox;
        QGroupBox *formGroupBox;
        QTextEdit *smallEditor;
        QTextEdit *bigEditor;
        QLabel *labels[NumGridRows];
        QLineEdit *lineEdits[NumGridRows];
        QPushButton * m_increment_base_button;
        QPushButton * m_decrement_base_button;
        QLineEdit * m_base_line_edit;


    QVBoxLayout *m_mainLayout;
    cPrimeCanvas* getPrimeCanvas() {return m_primeCanvas;}


    QLineEdit * QLedit1;// this is Base??
    QLineEdit * QLedit2;
    QLineEdit * QLedit3;
    QLineEdit * QLedit4;
    QLineEdit * QLedit5;
    QLineEdit * QLedit6;
    QLineEdit * QLedit7;
    QLineEdit * QLedit8;
    QLineEdit * QLedit9;

    QList<int>              m_primes;
    QVector<QList<int>*>    m_factors;
    int                     m_largest_integer_factored;

private slots:
    void incrementBase( );
    void decrement_base();
    void nextBase();
    void previousBase();
    void set_new_base(int);
    void set_new_base(const QString &);
    void set_new_base_from_line_edit( );

};
#endif // MAINWINDOW_H
