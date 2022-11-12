#include <QDebug>
#include <algorithm>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)     
{
    m_largest_integer_factored = 1;
    createMenu();
    createHorizontalGroupBox();
    createGridGroupBox();
    createFormGroupBox();
    initialize_prime_numbers();

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Muliplicative inverses in Z/N");
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setMenuBar(menuBar);
    m_mainLayout->addWidget(m_horizontalGroupBox);
    m_mainLayout->addWidget(gridGroupBox);
    m_mainLayout->addWidget(formGroupBox);
    //m_mainLayout->addWidget(bigEditor);

    m_active_prime_canvas = new cPrimeCanvas(this);// if it has no parent, it should live separately on the screen.
    m_active_prime_canvas->show();
    m_active_prime_canvas->move(0,this->height());
    //m_active_prime_canvas = new cPrimeCanvas(this, this);// if it has no parent, it should live separately on the screen.
    m_prime_canvas_collection.append(m_active_prime_canvas);
    //m_mainLayout->addWidget(m_active_prime_canvas);
    QWidget *widget = new QWidget();
    widget->setLayout(m_mainLayout);
    setCentralWidget(widget);


    connect(m_increment_base_button, &QPushButton::clicked, this, &MainWindow::incrementBase);
    connect(QLedit2, &QLineEdit::editingFinished, this, &MainWindow::set_new_base_from_line_edit);
    connect(m_increment_base_button, &QPushButton::clicked, this, &MainWindow::incrementBase);
    connect(m_decrement_base_button, &QPushButton::clicked, this, &MainWindow::decrement_base);

}
void MainWindow::initialize_prime_numbers(){
    m_factors.reserve(2000);
    m_factors.append( new QList<int> );
    m_factors.append( new QList<int> );
    m_factors.append( new QList<int> );
    m_factors.append( new QList<int> );
    m_factors[1]->append(1);
    m_factors[2]->append(2);
    m_factors[3]->append(3);
    m_largest_integer_factored = 3;
    m_primes.append(2);
    m_primes.append(3);
}
MainWindow::~MainWindow()
{

}


void MainWindow::incrementBase(){
    //maybeSaveDotPage();
    m_active_prime_canvas->increment_base();
}
void MainWindow::decrement_base(){
    //maybeSaveDotPage();
    m_active_prime_canvas->decrement_base();
}
void MainWindow::nextBase(){
    incrementBase();
}
void MainWindow::set_new_base(const QString & base){
    m_active_prime_canvas->change_base(base.toInt());
}
void MainWindow::set_new_base(int n){
    m_active_prime_canvas->change_base(n);
}
void MainWindow::previousBase(){
    if (m_active_prime_canvas->get_base() > 3){
       m_active_prime_canvas->decrement_base();
    }
}
void MainWindow::set_UI_base(int newbase){
    QLedit1->setText(QString::number(newbase-1));
    QLedit2->setText(QString::number(newbase));
    QLedit3->setText(QString::number(newbase+1));
    QStringList factors;
    foreach (int i, *   get_factors(newbase-1) ) {
        factors << QString::number(i);
    }
    QLedit4->setText(factors.join(" "));
    factors.clear();
    foreach (int i, *   get_factors(newbase) ) {
        factors << QString::number(i);
    }
    QLedit5->setText(factors.join(" "));
    m_base_line_edit->setText(QString::number(newbase));
    factors.clear();
    foreach (int i, *   get_factors(newbase+1) ) {
        factors << QString::number(i);
    }
    QLedit6->setText(factors.join(" "));

    QLedit8->setText(euler(newbase));


}
void MainWindow::set_new_base_from_line_edit( ){
    m_active_prime_canvas->change_base(get_UI_base());
}

void MainWindow::createMenu()
{
    menuBar = new QMenuBar;
    /*
    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);
    connect(exitAction, &QAction::triggered, this, &QDialog::accept);
   */
}

void MainWindow::createHorizontalGroupBox()
{
    m_horizontalGroupBox = new QGroupBox("Horizontal layout");
    m_horizontalGroupBox->setMaximumHeight(140);
    QHBoxLayout *layout = new QHBoxLayout;
    m_increment_base_button = new QPushButton ("++");
    m_decrement_base_button = new QPushButton ("--");
    QLabel * label = new QLabel("Base:");
    m_base_line_edit = new QLineEdit();
    m_increment_base_button->setMaximumWidth(50);
    m_decrement_base_button->setMaximumWidth(50);
    m_base_line_edit->setMaximumWidth(50);

    layout->addWidget(m_increment_base_button);
    layout->addWidget(m_decrement_base_button);
    layout->addWidget(label);
    layout->addWidget(m_base_line_edit);
    m_horizontalGroupBox->setLayout(layout);
}






void MainWindow::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("Grid layout"));
    gridGroupBox->setMaximumHeight(200);
    QGridLayout *layout = new QGridLayout;

    QLabel * label1 = new QLabel ("Base - 1");
    QLabel * label2 = new QLabel ("Base");
    QLabel * label3 = new QLabel ("Base + 1");
    layout->addWidget(label1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(label3,0,3);

    QLabel * label4 = new QLabel ("Number");
    QLabel * label5 = new QLabel ("Factors");
    QLabel * label6 = new QLabel ("Totient");
    layout->addWidget(label4,1,0);
    layout->addWidget(label5,2,0);
    layout->addWidget(label6,3,0);

    QLedit1 = new QLineEdit();
    QLedit2 = new QLineEdit();
    QLedit3 = new QLineEdit();
    QLedit4 = new QLineEdit(); // this is Base??
    QLedit5 = new QLineEdit();
    QLedit6 = new QLineEdit();
    QLedit7 = new QLineEdit();
    QLedit8 = new QLineEdit();
    QLedit9 = new QLineEdit();
    layout->addWidget(QLedit1,1,1);
    layout->addWidget(QLedit2,1,2);
    layout->addWidget(QLedit3,1,3);
    layout->addWidget(QLedit4,2,1);
    layout->addWidget(QLedit5,2,2);
    layout->addWidget(QLedit6,2,3);
    layout->addWidget(QLedit7,3,1);
    layout->addWidget(QLedit8,3,2);
    layout->addWidget(QLedit9,3,3);

    smallEditor = new QTextEdit;
    smallEditor->setPlainText(tr("This widget takes up about two thirds of the "
                                 "grid layout."));
    //layout->addWidget(smallEditor, 0, 2, 4, 1);

    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}

void MainWindow::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Form layout"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
    layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
    layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
    formGroupBox->setLayout(layout);
    formGroupBox->setVisible(false);
}

void MainWindow::compute_primes_and_factors(int upto_N){
    if ( upto_N < m_largest_integer_factored){
        return;
    }
    //qDebug() << "->" << upto_N << "largest factored" << m_largest_integer_factored;
    for (int  n = m_largest_integer_factored + 1; n <= upto_N+1; n++){
        foreach (int p, m_primes){
            //qDebug() << "n" << n << "p" << p;
            if ( n < p * p ){
                m_primes.append(n);
                //qDebug() << "  " << n << "is prime.";
                QList<int> * newlist = new QList<int>;
                newlist->append(n);
                m_factors.append(newlist);
                break;
            }
            if (n % p == 0){
                QList<int> * newlist = new QList<int>;
                //qDebug() << "  " << p << " is a divider";
                newlist ->append (p);
                newlist->append(*m_factors[n /  p] );
                //qDebug() << "   " << n << p << n/p << "other factors are" << *m_factors[n/p];
                m_factors.append(newlist);
                break;
            }
        }
    }
    m_largest_integer_factored = upto_N + 1;
    //qDebug() << "end";

}
QString MainWindow::euler(int n){

    QList<int> result;
    int previous_factor = 0;
    compute_primes_and_factors(n);
    for (int i = 0; i < m_factors[n]->length(); i++){
        int this_factor = m_factors[n]->at(i);
        if (this_factor != previous_factor){
            if (this_factor == 2){ continue;}
            QList<int> * new_factors = m_factors[this_factor - 1];
            result.append(*new_factors);
        } else{
            result.append( this_factor );
        }
    }
    std::sort(result.begin(), result.end());
    QString output;
    foreach (int i, result){
        output += QString::number(i) + " ";
    }
    return output.trimmed();
}
