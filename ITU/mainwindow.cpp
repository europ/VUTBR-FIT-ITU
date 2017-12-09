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
#include <QApplication>
#include <QFrame>
#include <QStyle>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "macros.hpp"

#define MAX_NETWORKS 10


bool geci = false;
QFrame * lines[MAX_NETWORKS];
QPushButton * ssid_names[MAX_NETWORKS];
int wifinumber;
Data d;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

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

        connect(ssid_names[i], SIGNAL(released()), this, SLOT(show_network_info()));
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
}


void MainWindow::update(){
    LOAD(d);
    unsigned size = SIZE(d);


    std::cout << size << std::endl;


    for(unsigned i = 0; i< MAX_NETWORKS;i++){

        int y;

        if(i<size){
            y = atoi(d.get_SIGNAL(i).c_str());
        }


        if(i < size){;
            lines[i]->setGeometry(50*i+8,4+4*(100-y),15,400);
            ssid_names[i]->setText(d.get_SSID(i).c_str());
        }
        else{
             lines[i]->setGeometry(0,404,481,1);
             ssid_names[i]->setText("");
        }

        lines[i]->repaint();
        ssid_names[i]->repaint();
    }


}

void MainWindow::show_network_info(){

    QPushButton * button = (QPushButton*)sender();
    QString qstrssid = button->text();
    std::string ssid = qstrssid.toUtf8().constData();


    //get index of clicked network
    unsigned index;

    for(unsigned i=0;i<d.size();i++){
        if(d.get_SSID(i) == ssid){
            index = i;
            break;
        }
    }

    //printf("%d\n",index);

    QWidget *wdg = new QWidget;
    wdg->setMinimumSize(400, 300);
    wdg->setMaximumSize(400, 300);
    wdg->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    wdg->setWindowTitle("Detailed WI-FI information");


    QVBoxLayout *layout = new QVBoxLayout();


    QLabel *label[10];
    for(int i=0; i< 10; i++){
        label[i] = new QLabel(this);
        //label[i]->setText("Random String");
        //layout->addWidget(label[i]);
    }
   // wdg->setLayout(layout);

    label[0]->setText("gecc");
    label[1]->setText("gecc");
    label[2]->setText("gecc");
    label[3]->setText("gecc");
    label[4]->setText("gecc");
    label[5]->setText("gecc");
    label[6]->setText("gecc");
    label[7]->setText("gecc");
    label[8]->setText("gecc");
    label[9]->setText("gecc");

    for(int i=0; i< 10; i++){
        layout->addWidget(label[i]);
    }

    wdg->setLayout(layout);

    wdg->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            wdg->size(),
            qApp->desktop()->availableGeometry()
        )
    );

    wdg->show();
}
