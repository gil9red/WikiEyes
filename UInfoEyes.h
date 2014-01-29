#ifndef UINFOEYES_H
#define UINFOEYES_H

#include <QtGui>
#include <QtCore>

#include "USupport.h"
#include "UEye.h"
#include "UEyeWidget.h"
#include "USimpleButton.h"
#include "UAboutProgram.h"
#include "USettings.h"

/// Класс информации о глазах
/// т.к. глаза будут абсолютно одинаковы,
/// удобнее будет хранить информацию о них
/// в одном объекте
class UInfoEyes: public QObject
{
    Q_OBJECT

public:
    UInfoEyes(QObject *parent = 0)
        : QObject(parent)
    {
        number = 2;
        diameter = minimalWidthEye;
    }

public:
    int number;
    int diameter;

public slots:
    void setNumber(int n){number = n;}
    void setDiameter(int d){diameter = d;}

    void infoFrom(const UInfoEyes *other)
    {
        number = other->number;
        diameter = other->diameter;
    }
};

static UInfoEyes infoEyes;
static const UInfoEyes defaultInfoEyes;

#endif // UINFOEYES_H
