#ifndef USUPPORT_H
#define USUPPORT_H

#include <QtGui>
#include <QtCore>

class UEllipse
{
public:
    UEllipse()
        : x1(0), y1(0),
          rx(0), ry(0)
    {}

    UEllipse(double x1, double y1, double rx, double ry)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->rx = rx;
        this->ry = ry;
    }

public:
    double x1;
    double y1;
    double rx;
    double ry;
};

class ULine
{
public:
    ULine()
        : x1(0), y1(0),
          x2(0), y2(0)
    {}

    ULine(double x1, double y1, double x2, double y2)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

public:
    double x1;
    double y1;
    double x2;
    double y2;
};


class UResultCrossLineAndEllipse
{
public:
    double x1;
    double y1;
    double x2;
    double y2;
};


const double eps = 0.00001;

class UIntersection
{
public:
    // функция которая счетает пересиченния еллипса и прямой
    // когда пересечений нету возврасчает false иначе true и
    // в масив Res присваевается точки пересичение
    static bool isEllipseAndDirect(const UEllipse *ellipse, const ULine *line,
                                   UResultCrossLineAndEllipse *result)
    {
        const double dx = line->x1 - line->x2;

        // если какойто радиус равен 0
        if(qAbs(ellipse->rx) < eps
                || qAbs(ellipse->ry) < eps )
        {
            if(qAbs(ellipse->rx) < eps && qAbs(line->x1-ellipse->x1) < eps
                    && qAbs(line->x2-ellipse->x1) < eps)
            {
                result->x1 = ellipse->x1;
                result->y1 = ellipse->y1 - ellipse->ry;
                result->x2 = ellipse->x1;
                result->y2 = ellipse->y1 + ellipse->ry;
                return true;
            }
            if(qAbs(ellipse->ry) < eps && qAbs(line->y1-ellipse->y1) < eps
                    && qAbs(line->y2-ellipse->y1) < eps)
            {
                result->x1 = ellipse->x1 - ellipse->rx;
                result->y1 = ellipse->y1;
                result->x2 = ellipse->x1 + ellipse->rx;
                result->y2 = ellipse->y1;
                return true;
            }
        }

        if (qAbs(dx) < eps)
        {
            // вертикальная примая
            const double nx = line->x1 - ellipse->x1;

            // пересечения нету
            if( nx < -ellipse->rx || ellipse->rx < nx || qAbs(ellipse->rx) < eps )
                return false;

            // возвращаю результат в масив result
            result->x1 = nx;
            result->y1 = sqrt( ellipse->ry*ellipse->ry * (1 - nx*nx/(ellipse->rx*ellipse->rx)) );
            result->x2 = nx;
            result->y2 =-result->y1;

        }else
        {
            const double dy = line->y1 - line->y2;
            // lnk и lnb - коефициенти прямой по формуле lnk * x + lnb  ==  y
            const double lnk= dy / dx;
            const double lnb=(ellipse->x1*dy + line->x1*line->y2 - line->y1 * line->x2 - ellipse->y1*dx )/dx;

            // получаем уравненние пересичения: a0 x^2 + a1 x + a2  ==  0
            const double a0 = lnk * lnk + ellipse->ry * ellipse->ry / ( ellipse->rx * ellipse->rx);
            const double a1 =   2 * lnb * lnk;
            const double a2 = lnb * lnb - ellipse->ry * ellipse->ry;

            // решения квадратного уровненние a0 x^2 + a1 x + a2  ==  0
            // ето и будет координати X пересечений
            const double disc = a1*a1 - 4 * a0 * a2;

            // пересичения нету
            if (disc  <  0 || qAbs(a0) < eps )
                return false;

            // возвращаю результат в масив res
            result->x1 = (-a1 - sqrt(disc) ) / ( 2 * a0);
            result->y1 = lnk * result->x1 + lnb;
            result->x2 = (-a1 + sqrt(disc) ) / ( 2 * a0);
            result->y2 = lnk * result->x2 + lnb;

        }

        result->x1 += ellipse->x1;
        result->y1 += ellipse->y1;
        result->x2 += ellipse->x1;
        result->y2 += ellipse->y1;

        return true;
    }
};

class USupport
{
public:
    // процент от числа
    static double percentNumber(double number, int percent)
    { return percent < 0 ? number : (number / 100) * percent; }
};

const double minimalWidthEye = 50;
const double minimalHeightEye = 50;

const double maximalWidthEye = 350;
const double maximalHeightEye = 350;

const int minimalNumberEyes = 1;
const int maximalNumberEyes = 10;

#endif // USUPPORT_H
