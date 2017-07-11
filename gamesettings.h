#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QDialog>

namespace Ui {
class gameSettings;
}

class gameSettings : public QDialog
{
    Q_OBJECT

public:
    explicit gameSettings(QWidget *parent = 0);
    ~gameSettings();

private:
    Ui::gameSettings *ui;
};

#endif // GAMESETTINGS_H
