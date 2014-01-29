#ifndef USETTINGS_H
#define USETTINGS_H

#include <QtGui>
#include <QtCore>

namespace Ui {
class USettings;
}

#include "ui_USettings.h"

class USettings: public QDialog
{
    Q_OBJECT
    
public:
    explicit USettings(QWidget *parent = 0);
    ~USettings();
    
    Ui::USettings * gui();

private:
    Ui::USettings *ui;
};

#endif // USETTINGS_H
