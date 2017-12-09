#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLine>
#include <QDebug>
#include <QTimer>
#include <QListView>
#include "analyser.hpp"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#define MAX_NETWORKS 10

#define LOAD(d) while(d.refresh() != true);
#define DEBUG(d) d.DEBUG();
#define SIZE(d) d.size();

bool geci = false;
QFrame * lines[MAX_NETWORKS];
QPushButton * ssid_names[MAX_NETWORKS];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    Data d;
    LOAD(d); // load data

    unsigned size = SIZE(d);

    DEBUG(d); // print info

    std::string tmp = d.get_SSID(5);


    ui->setupUi(this);


    //set background of window
    this->setStyleSheet("background-color:#264f93 ;");

//#001d77   #4286f4  buttons:#eae600

    //set button colors to yellow
    ui->pushButton->setStyleSheet("background-color: #f4f38b; color: black");



    //combo box settings
    QListView * listView = new QListView(ui->comboBox);
    listView->setStyleSheet("QListView::item { margin:3px; }");
    ui->comboBox->setView(listView);

    ui->comboBox->setStyleSheet("background-color: #f4f38b; color: black");
    ui->radioButton->setStyleSheet("background-color: #f4f38b; color: black");
    ui->radioButton_2->setStyleSheet("background-color: #f4f38b; color: black");
    ui->radioButton_3->setStyleSheet("background-color: #f4f38b; color: black");



    //labels settings
    ui->label->setStyleSheet("color: white");
    ui->label_2->setStyleSheet("color: white");
    ui->label_4->setStyleSheet("color: white");
    ui->label_5->setStyleSheet("color: white");

    //ui->line->setLine(0,0,200,200)
   // QLine *line5;
    //line5 = new QLine();
   // line5->setLine(0,0,200,200);


    //colors for networks
    QString colours[10] = {"cyan", "magenta", "red",
                          "darkRed", "darkCyan", "darkMagenta",
                          "green","darkGreen", "yellow",
                          "blue"};

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



    for(unsigned i = 0; i< MAX_NETWORKS;i++){
        lines[i] = new QFrame(ui->frame);
        ssid_names[i] = new QPushButton(this);
        //lines[i]->setFrameShape(QFrame::HLine);
        //lines[i]->setFrameShadow(QFrame::Sunken);
        int y;

        if(i<size){
            y = atoi(d.get_SIGNAL(i).c_str());
        }

        if(i<size){
            //lines[i]->setGeometry(0,400-y,481,1);
            lines[i]->setGeometry(50*i+8,4+4*(100-y),15,400);
        }
        else{
            lines[i]->setGeometry(0,404,481,1);
        }

        lines[i]->setStyleSheet( QString("background-color:%1;").arg(colours[i]));// background-color: colours[i]; ");
        ssid_names[i]->setText(d.get_SSID(i).c_str());
        ssid_names[i]->move(50*i+50, 500);
        ssid_names[i]->setFixedSize( 60, 20 );
        ssid_names[i]->setStyleSheet( "background-color: #264f93 ;border: 0px;color: white ; text-align: center");
        QFont font = ssid_names[i]->font();
        font.setPointSize(7);
        ssid_names[i]->setFont(font);


    }


 /*   QPushButton *buttonA = new QPushButton(this);
    buttonA->setText("ans");
    buttonA->move(10, 10);
    buttonA->setStyleSheet( "background-color: #264f93 ;border: 0px;color: white ");
    buttonA->setFixedSize( 58, 20 );
    //buttonA->resize(buttonA->minimumSize());

*/

    ui->pushButton_3->setStyleSheet("background-color: red; color: #f4f38b ");
    ui->pushButton_2->setStyleSheet("background-color: #f4f38b; color: black");


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10000);


}

//}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::button2_press(){
    QPushButton * button = (QPushButton*)sender();

    ui->pushButton_3->setStyleSheet("background-color: red; color: #f4f38b ");
    ui->pushButton_2->setStyleSheet("background-color: #f4f38b; color: black");
    //ui->label->setText(button->text());
}


void MainWindow::button3_press(){
    QPushButton * button = (QPushButton*)sender();
    ui->pushButton_2->setStyleSheet("background-color: red; color: #f4f38b ");
    ui->pushButton_3->setStyleSheet("background-color: #f4f38b; color: black");
    //ui->label->setText(button->text());
}


void MainWindow::update(){
    Data d;

    LOAD(d);
    unsigned size = SIZE(d);


    std::cout << size << std::endl;


    for(unsigned i = 0; i< MAX_NETWORKS;i++){

        int y;

        if(i<size){
            y = atoi(d.get_SIGNAL(i).c_str());
        }


        if(i < size){
             //lines[i]->setGeometry(0,400-y,481,1);
            lines[i]->setGeometry(50*i+8,4+4*(100-y),15,400);
        }
        else{
             lines[i]->setGeometry(0,404,481,1);
        }
        //printf("i = %d\n",i);

    }


}

