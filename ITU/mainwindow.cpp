#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLine>
#include <QDebug>
#include "analyser.hpp"
#include <string>


#define LOAD(d) while(d->refresh() != true);
#define DEBUG(d) d->DEBUG();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    Data* d = new Data();
    LOAD(d); // load data

    //DEBUG(d); // print info

    std::string tmp =  d->get_SSID(5);


    ui->setupUi(this);


    //set background of window
    this->setStyleSheet("background-color: #001d77;");



    //set button colors to yellow
    ui->pushButton->setStyleSheet("background-color: #eae600; color: black");
    ui->pushButton_3->setStyleSheet("background-color: red; color: #eae600 ");
    ui->pushButton_2->setStyleSheet("background-color: #eae600; color: black");

    ui->comboBox->setStyleSheet("background-color: #eae600; color: black");

    ui->radioButton->setStyleSheet("background-color: #eae600; color: black");
    ui->radioButton_2->setStyleSheet("background-color: #eae600; color: black");
    ui->radioButton_3->setStyleSheet("background-color: #eae600; color: black");


    ui->label->setStyleSheet("color: white");
    ui->label_2->setStyleSheet("color: white");
    ui->label_3->setStyleSheet("color: white");
    ui->label_3->setText(tmp.c_str());


    //ui->line->setLine(0,0,200,200)
   // QLine *line5;
    //line5 = new QLine();
   // line5->setLine(0,0,200,200);


    QFrame *lines[5];
    for(int i = 0; i< 5;i++){
        lines[i] = new QFrame(ui->frame);
        lines[i]->setFrameShape(QFrame::HLine);
        lines[i]->setFrameShadow(QFrame::Sunken);
        lines[i]->setGeometry(0,100+5*i,481,1);
        lines[i]->setStyleSheet(" border: 1px solid red;");
    }


    //vytvaranie ciari

    /*QFrame *line5;
    line5 = new QFrame(ui->frame);
    line5->setFrameShape(QFrame::HLine);
    line5->setFrameShadow(QFrame::Sunken);
    line5->setGeometry(0,100,481,1);
    //line5->setObjectName("myObject");
    //line5->setStyleSheet("#myObject { border: 1px solid red; }");
    line5->setStyleSheet(" border: 1px solid red;");
    */


    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(button2_press()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(button3_press()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::button2_press(){
    QPushButton * button = (QPushButton*)sender();

    ui->pushButton_3->setStyleSheet("background-color: red; color: #eae600 ");
    ui->pushButton_2->setStyleSheet("background-color: #eae600; color: black");
    //ui->label->setText(button->text());
}


void MainWindow::button3_press(){
    QPushButton * button = (QPushButton*)sender();
    ui->pushButton_2->setStyleSheet("background-color: red; color: #eae600 ");
    ui->pushButton_3->setStyleSheet("background-color: #eae600; color: black");
    //ui->label->setText(button->text());
}
