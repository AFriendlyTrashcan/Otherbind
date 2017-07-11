#include "gamesettings.h"
#include "ui_gamesettings.h"

gameSettings::gameSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameSettings)
{
    ui->setupUi(this);
}

gameSettings::~gameSettings()
{
    delete ui;
}
