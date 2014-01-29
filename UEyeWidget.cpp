#include "UEyeWidget.h"

/// PUBLIC
UEyeWidget::UEyeWidget(QWidget *parent)
    : QWidget(parent),
    d_percentIrisRadiusX(30),
    d_percentIrisRadiusY(30),

    d_percentPupilRadiusX(55),
    d_percentPupilRadiusY(55)
{       
    positionLook = QPoint(0, 0);

    setDiameter(minimalWidthEye);


    setBrush(QBrush(Qt::white));
    setPen(QPen(Qt::black, 2.0));

    setBrushIris(QBrush(Qt::black));
    setPenIris(QPen(Qt::black, 1.0));

    setBrushPupil(QBrush(Qt::black));
    setPenPupil(QPen(Qt::white, 1.0));
}

void UEyeWidget::setEye(UEye eye)
{ this->eye = eye; }
UEye & UEyeWidget::getPointerEye()
{ return eye; }
UEye UEyeWidget::getEye()
{ return eye; }

void UEyeWidget::setVisibleIris(bool visible)
{ eye.setVisibleIris(visible); }
void UEyeWidget::setVisiblePupil(bool visible)
{ eye.setVisiblePupil(visible); }

bool UEyeWidget::isVisibleIris()
{ return eye.isVisibleIris(); }
bool UEyeWidget::isVisiblePupil()
{ return eye.isVisiblePupil(); }

void UEyeWidget::setIris(const UIris iris)
{ eye.setIris(iris); }
void UEyeWidget::setPupil(const UPupil pupil)
{ eye.setPupil(pupil); }

UIris & UEyeWidget::iris()
{ return eye.iris(); }
UPupil & UEyeWidget::pupil()
{ return eye.pupil(); }


void UEyeWidget::setDiameter(double diameter)
{ setFixedSize(diameter, diameter); }
void UEyeWidget::setBrush(const QBrush brush)
{ eye.setBrush(brush); }
void UEyeWidget::setPen(const QPen pen)
{ eye.setPen(pen); }
QPoint UEyeWidget::center()
{ return eye.center(); }
double UEyeWidget::radiusX()
{ return eye.radiusX(); }
double UEyeWidget::radiusY()
{ return eye.radiusY(); }
QBrush UEyeWidget::brush()
{ return eye.brush(); }
QPen UEyeWidget::pen()
{ return eye.pen(); }


void UEyeWidget::setBrushIris(const QBrush brush)
{ eye.iris().setBrush(brush); }
void UEyeWidget::setPenIris(const QPen pen)
{ eye.iris().setPen(pen); }
QPoint UEyeWidget::centerIris()
{ return eye.iris().center(); }
void UEyeWidget::setRadiusXIris(double radius)
{ return eye.iris().setRadiusX(radius); }
void UEyeWidget::setRadiusYIris(double radius)
{ return eye.iris().setRadiusY(radius); }
double UEyeWidget::radiusXIris()
{ return eye.iris().radiusX(); }
double UEyeWidget::radiusYIris()
{ return eye.iris().radiusY(); }
QBrush UEyeWidget::brushIris()
{ return eye.iris().brush(); }
QPen UEyeWidget::penIris()
{ return eye.iris().pen(); }


void UEyeWidget::setBrushPupil(const QBrush brush)
{ eye.pupil().setBrush(brush); }
void UEyeWidget::setPenPupil(const QPen pen)
{ eye.pupil().setPen(pen); }
QPoint UEyeWidget::centerPupil()
{ return eye.pupil().center(); }
void UEyeWidget::setRadiusXPupil(double radius)
{ return eye.pupil().setRadiusX(radius); }
void UEyeWidget::setRadiusYPupil(double radius)
{ return eye.pupil().setRadiusY(radius); }
double UEyeWidget::radiusXPupil()
{ return eye.pupil().radiusX(); }
double UEyeWidget::radiusYPupil()
{ return eye.pupil().radiusY(); }
QBrush UEyeWidget::brushPupil()
{ return eye.pupil().brush(); }
QPen UEyeWidget::penPupil()
{ return eye.pupil().pen(); }

int UEyeWidget::percentIrisRadiusX()
{ return d_percentIrisRadiusX; }
int UEyeWidget::percentIrisRadiusY()
{ return d_percentIrisRadiusY; }

int UEyeWidget::percentPupilRadiusX()
{ return d_percentPupilRadiusX; }
int UEyeWidget::percentPupilRadiusY()
{ return d_percentPupilRadiusY; }


/// PUBLIC SLOTS
void UEyeWidget::lookThere(QPoint position)
{
    positionLook = mapFromGlobal(position);
    update();
}

void UEyeWidget::setPercentIrisRadiusX(int percent)
{ d_percentIrisRadiusX = percent; }
void UEyeWidget::setPercentIrisRadiusY(int percent)
{ d_percentIrisRadiusY = percent; }

void UEyeWidget::setPercentPupilRadiusX(int percent)
{ d_percentPupilRadiusX = percent; }
void UEyeWidget::setPercentPupilRadiusY(int percent)
{ d_percentPupilRadiusY = percent; }

/// PROTECTED
void UEyeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int indent = 3;

    /// По размерам окна определим примерно размер глаз
    /// рассчет будет по высоте и ширине
    double rXFromWidth = (width() - indent * 2) / 2;
    double rYFromHeigth = (height() - indent * 2) / 2;

    double radiusXEye = qMin(rXFromWidth, rYFromHeigth);
    double radiusYEye = radiusXEye;

    double radiusXIris = USupport::percentNumber(radiusXEye, d_percentIrisRadiusX);
    double radiusYIris = USupport::percentNumber(radiusYEye, d_percentIrisRadiusY);

    double radiusXPupil = USupport::percentNumber(radiusXIris, d_percentPupilRadiusX);
    double radiusYPupil = USupport::percentNumber(radiusYIris, d_percentPupilRadiusY);


    int x = radiusXEye + indent;
    int y = radiusYEye + indent;

    eye.setRadiusX(radiusXEye);
    eye.setRadiusY(radiusYEye);
    eye.setCenter(QPoint(x, y));


    /// Радужка глаза
    UIris &iris = eye.iris();
    iris.setCenter(positionLook);
    iris.setRadiusX(radiusXIris);
    iris.setRadiusY(radiusYIris);
    /// Радужка глаза

    /// Зрачок глаза
    UPupil &pupil = eye.pupil();
    pupil.setRadiusX(radiusXPupil);
    pupil.setRadiusY(radiusYPupil);
    /// Зрачок глаза

    eye.draw(&painter);
}
