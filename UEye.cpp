#include "UEye.h"

/// UEye PUBLIC
UEye::UEye()
    : visibleIris(true),
      visiblePupil(true)
{    
}

void UEye::setIris(const UIris iris)
{ d_iris = iris; }
void UEye::setPupil(const UPupil pupil)
{ d_pupil = pupil; }

UIris & UEye::iris()
{ return d_iris; }
UPupil & UEye::pupil()
{ return d_pupil; }

void UEye::draw(QPainter *painter)
{
    drawEye(painter);    
    drawIris(painter);
    drawPupil(painter);
}

void UEye::setVisibleIris(bool visible)
{ visibleIris = visible; }
void UEye::setVisiblePupil(bool visible)
{ visiblePupil = visible; }
bool UEye::isVisibleIris()
{ return visibleIris; }
bool UEye::isVisiblePupil()
{ return visiblePupil; }

/// UEye PRIVATE
void UEye::drawEye(QPainter *painter)
{
    painter->save();
    painter->setBrush(d_brush);
    painter->setPen(d_pen);
    painter->drawEllipse(d_center, d_radiusX, d_radiusY);
    painter->restore();
}

void UEye::drawIris(QPainter *painter)
{
    int x1 = d_center.x();
    int y1 = d_center.y();

    int x2 = d_iris.d_center.x();
    int y2 = d_iris.d_center.y();

    double boundingWidth = d_radiusX - d_iris.d_radiusX;
    double boundingHeight = d_radiusY - d_iris.d_radiusY;

    // Установим размер ограничивающего эллипса, он будет в
    // процентах от размера глаз
    boundingWidth = USupport::percentNumber(boundingWidth, 80);
    boundingHeight = USupport::percentNumber(boundingHeight, 80);

    UEllipse boundingEllipse(d_center.x(), d_center.y(),
                             boundingWidth, boundingHeight);

    int a = pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2);
    int b = pow(d_radiusX, 2) - pow(USupport::percentNumber(d_radiusX - d_iris.d_radiusX, 130), 2);

    if(a >= b)
    {
        ULine line(d_center.x(), d_center.y(),
                   d_iris.d_center.x(), d_iris.d_center.y());
        UResultCrossLineAndEllipse result;

        if(UIntersection::isEllipseAndDirect(&boundingEllipse, &line, &result))
        {
            if(d_center.x() == d_iris.d_center.x())
            {
                if(d_center.y() < d_iris.d_center.y())
                {
                    d_iris.d_center.setX(result.x1);
                    d_iris.d_center.setY(result.y1);

                }else
                {
                    d_iris.d_center.setX(result.x2);
                    d_iris.d_center.setY(result.y2);
                }

            }else if(d_center.x() > d_iris.d_center.x())
            {
                d_iris.d_center.setX(result.x1);
                d_iris.d_center.setY(result.y1);

            }else if(d_center.x() < d_iris.d_center.x())
            {
                d_iris.d_center.setX(result.x2);
                d_iris.d_center.setY(result.y2);
            }
        }
    }

    painter->save();
    painter->translate(d_iris.d_center.x(),
                       d_iris.d_center.y());

    painter->setBrush(d_iris.d_brush);
    painter->setPen(d_iris.d_pen);

    if(visibleIris)
        painter->drawEllipse(QPoint(0, 0), d_iris.d_radiusX, d_iris.d_radiusY);

    painter->restore();
}

void UEye::drawPupil(QPainter *painter)
{
    painter->save();
    painter->translate(d_iris.d_center.x(),
                       d_iris.d_center.y());

    painter->setBrush(d_pupil.d_brush);
    painter->setPen(d_pupil.d_pen);

    if(visiblePupil)
        painter->drawEllipse(QPoint(0, 0), d_pupil.d_radiusX, d_pupil.d_radiusY);
//    // TODO
//    painter->rotate(90);
//    painter->drawEllipse(QPoint(0, 0), d_pupil.d_radiusX, d_pupil.d_radiusY);
//    //
//    QImage image(qApp->applicationDirPath()
//                 + "\\"
//                 + "7.png");
//    double width = d_pupil.d_radiusX * 2;
//    double height = d_pupil.d_radiusY * 2;
//    image = image.scaled(width, height);
//    painter->drawImage(-image.width()/2, -image.height()/2, image);

    painter->restore();
}

