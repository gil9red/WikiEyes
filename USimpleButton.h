#ifndef USIMPLEBUTTON_H
#define USIMPLEBUTTON_H

#include <QtGui>
#include <QtCore>

class USimpleButton: public QWidget
{
    Q_OBJECT

public:
    USimpleButton(QString pathActivate, QString pathDeactivate, QWidget *parent = 0)
        : QWidget(parent),
          press(false)
    {
        setPixmapActivate(pathActivate);
        setPixmapDeactivate(pathDeactivate);
        current = pixmapDeactivate;
    }
    void setPixmapActivate(QString path)
    { pixmapActivate = QPixmap(path); }
    void setPixmapDeactivate(QString path)
    { pixmapDeactivate = QPixmap(path); }

private:
    QPixmap pixmapActivate;
    QPixmap pixmapDeactivate;
    QPixmap current;

    bool press;

signals:
    void clicked();

protected:
    void enterEvent(QEvent *)
    { current = pixmapActivate; }
    void leaveEvent(QEvent *)
    { current = pixmapDeactivate; }
    void mousePressEvent(QMouseEvent *)
    { press = true; }
    void mouseReleaseEvent(QMouseEvent *)
    {
        if(press)
            emit clicked();
        press = false;
        current = pixmapDeactivate;
        update();
    }
    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        current = current.scaled(size());
        painter.drawPixmap(0, 0, current);
    }
    void showEvent(QShowEvent *)
    { current = pixmapDeactivate; }
    void hideEvent(QShowEvent *)
    { current = pixmapDeactivate; }
};

#endif // USIMPLEBUTTON_H
