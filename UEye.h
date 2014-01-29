#ifndef UEYE_H
#define UEYE_H

#include <QtGui>
#include <QtCore>

#include "USupport.h"

#include <qmath.h>

class UEllipseObject
{
public:
    void setCenter(const QPoint center)
    { d_center = center; }

    void setRadiusX(const int radiusX)
    { d_radiusX = radiusX; }
    void setRadiusY(const int radiusY)
    { d_radiusY = radiusY; }

    void setBrush(const QBrush brush)
    { d_brush = brush; }
    void setPen(const QPen pen)
    { d_pen = pen; }


    QPoint center()
    { return d_center; }

    double radiusX()
    { return d_radiusX; }
    double radiusY()
    { return d_radiusY; }

    QBrush brush()
    { return d_brush; }
    QPen pen()
    { return d_pen; }

protected:
    QPoint d_center;
    double d_radiusX;
    double d_radiusY;

    QBrush d_brush;
    QPen d_pen;   
};


/// класс Радужка
class UIris: public UEllipseObject
{
    friend class UEye;
};

/// класс Зрачок
class UPupil: public UEllipseObject
{
    friend class UEye;
};


/// класс Глаз
class UEye: public UEllipseObject
{
public:
    UEye();

    void setIris(const UIris iris);
    void setPupil(const UPupil pupil);

    UIris & iris();
    UPupil & pupil();

    void draw(QPainter *painter);

    void setVisibleIris(bool visible);
    void setVisiblePupil(bool visible);

    bool isVisibleIris();
    bool isVisiblePupil();

private:
    UIris d_iris;
    UPupil d_pupil; 

    bool visibleIris;
    bool visiblePupil;

private:
    void drawEye(QPainter *painter);
    void drawIris(QPainter *painter);
    void drawPupil(QPainter *painter);
};


// ограничиващий эллипс. за него радужка не может выйти
//        UEllipse boundingEllipse(d_center.x(), d_center.y(),
//                                 d_radiusX-d_iris.d_radiusX-d_iris.d_radiusX/3,
//                                 d_radiusY-d_iris.d_radiusY-d_iris.d_radiusY/3);


//        QGradient *gradient = const_cast <QGradient *> (iris.brush.gradient());

//        if(gradient)
//        {
////            QRadialGradient *radialGradient = static_cast <QRadialGradient *> (gradient);

////            qDebug() << static_cast <QRadialGradient *> (gradient)->center() << iris.center;

//            QRadialGradient radialGradient(iris.center, iris.radiusX);

//            switch(gradient->type())
//            {
//            case QGradient::LinearGradient:
////                qDebug() << "LinearGradient";
//                break;

//            case QGradient::RadialGradient:
//                //qDebug() << "RadialGradient";
////                radialGradient->setCenter(iris.center);
////                iris.brush = QBrush(*radialGradient);
////                radialGradient.setColorAt(0.0, QColor(0, 0, 255));
////                radialGradient.setColorAt(1.0, QColor(10, 10, 10));
////                radialGradient.setColorAt(0.02, QColor(216,30,20));
//                radialGradient.setColorAt(0.5, QColor("#00A693"));
////                radialGradient.setColorAt(0.9, QColor("#00A693"));
//                radialGradient.setColorAt(1.0, QColor(0, 0, 0));
//                iris.brush = QBrush(radialGradient);
//                break;

//            case QGradient::ConicalGradient:
////                qDebug() << "ConicalGradient";
//                break;

//            case QGradient::NoGradient:
////                qDebug() << "NoGradient";
//                break;
//            };
//        }

#endif // UEYE_H
