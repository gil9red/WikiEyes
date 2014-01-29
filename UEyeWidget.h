#ifndef UEYEWIDGET_H
#define UEYEWIDGET_H

#include <QtGui>
#include <QtCore>

#include "UEye.h"

class UEyeWidget: public QWidget
{
    Q_OBJECT

public:
    UEyeWidget(QWidget *parent = 0);    

    void setEye(UEye eye);
    UEye & getPointerEye();
    UEye getEye();

    void setVisibleIris(bool visible);
    void setVisiblePupil(bool visible);

    bool isVisibleIris();
    bool isVisiblePupil();

    void setIris(const UIris iris);
    void setPupil(const UPupil pupil);

    UIris & iris();
    UPupil & pupil();

    void setDiameter(double diameter);
    void setBrush(const QBrush brush);
    void setPen(const QPen pen);
    QPoint center();
    double radiusX();
    double radiusY();
    QBrush brush();
    QPen pen();


    void setBrushIris(const QBrush brush);
    void setPenIris(const QPen pen);
    QPoint centerIris();
    void setRadiusXIris(double radius);
    void setRadiusYIris(double radius);
    double radiusXIris();
    double radiusYIris();
    QBrush brushIris();
    QPen penIris();


    void setBrushPupil(const QBrush brush);
    void setPenPupil(const QPen pen);
    QPoint centerPupil();
    void setRadiusXPupil(double radius);
    void setRadiusYPupil(double radius);
    double radiusXPupil();
    double radiusYPupil();
    QBrush brushPupil();
    QPen penPupil();

    int percentIrisRadiusX();
    int percentIrisRadiusY();

    int percentPupilRadiusX();
    int percentPupilRadiusY();    

private:
    UEye eye;
    QPoint positionLook;

    int d_percentIrisRadiusX;
    int d_percentIrisRadiusY;

    int d_percentPupilRadiusX;
    int d_percentPupilRadiusY;


public slots:
    void lookThere(QPoint position);
    void lookThere(int x, int y)
    { lookThere(QPoint(x, y)); }

    void setPercentIrisRadiusX(int percent);
    void setPercentIrisRadiusY(int percent);

    void setPercentPupilRadiusX(int percent);
    void setPercentPupilRadiusY(int percent);

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // UEYEWIDGET_H
