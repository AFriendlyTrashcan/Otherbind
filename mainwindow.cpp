#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "preferences.h"
#include "mixedplatforms.h"
#include "loopthread.h"
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <QThread>

using namespace std;

string langs[255][2];

int globalNewLang;
bool globalWorkaround = true;
int langCount = 0;

void loadConfigs(){
    ifstream configStream;
    string configRead;
    int readNumber = 0;
    configStream.open("../otherbind/configs");
    while(configStream >> configRead){
        switch(readNumber){
            case 0:
                globalNewLang = stoi(configRead);
                break;
            case 1:
                globalWorkaround = stoi(configRead);
                break;
            default:
                break;
        }
        readNumber++;
    }
}

void loadLangs(){
    ifstream langStream;
    string readLang;
    bool langSwitch = false;
    while(langStream >> readLang){
        if(!langSwitch){
            langs[langCount][0] = readLang;
        }else{
            langs[langCount][1] = readLang;
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    loadConfigs();
    ui->setupUi(this);
    loopThread *lt = new loopThread(true, 0);
    lt->start();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::setText(string text){
    ui->label->setText(QString::fromStdString(text));
}

void MainWindow::on_actionGlobal_Preferences_triggered(){
    Preferences pref(globalNewLang, globalWorkaround);
    pref.setModal(true);
    pref.exec();
    loadConfigs();
}

void MainWindow::on_pushButton_clicked()
{
    mixedPlatforms mp;
    if(mp.isUIRunning()){
        ui->label->setText(QString::fromStdString(mp.getAppID()));
    }else{
        ui->label->setText("No game currently running");
    }
}
