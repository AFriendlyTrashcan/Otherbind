#include "preferences.h"
#include "ui_preferences.h"
#include <fstream>
#include <string>
#include <QString>
#include <QDebug>

using namespace std;

string prefLangs[255][2];

int prefNewLang = 0;
bool prefWorkaround = false;

void prefLoadLangs();

Preferences::Preferences(int pNL, bool pW, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences){
    ui->setupUi(this);
    prefNewLang = pNL;
    prefWorkaround = pW;
    int prefLangCount = 0;
    ifstream langStream;
    string langLine;
    langStream.open("../otherbind/languages");
    while(getline(langStream, langLine)){
        if(prefLangCount == 0 || prefLangCount % 4 == 0){
            ui->setYourLayout->addItem(QString::fromStdString(langLine));
        }
        prefLangCount++;
    }
    ui->setYourLayout->setCurrentIndex(prefNewLang);
    ui->enableWorkaround->setChecked(prefWorkaround);

}

Preferences::~Preferences(){
    delete ui;
}

void Preferences::on_pushButton_clicked(){
    ofstream configOut;
    configOut.open("../otherbind/configs");
    configOut << '\n' << ui->setYourLayout->currentIndex() << '\n' << ui->enableWorkaround->checkState();
    this->close();
}

void Preferences::on_pushButton_2_clicked(){
    this->close();
}

void Preferences::on_pushButton_3_clicked()
{
    prefNewLang = 0;
    prefWorkaround = false;
    ui->setYourLayout->setCurrentIndex(prefNewLang);
    ui->enableWorkaround->setChecked(prefWorkaround);
}
