#ifndef UEYES_H
#define UEYES_H

#include <QtGui>
#include <QtCore>

#include "USupport.h"
#include "UEye.h"
#include "UEyeWidget.h"
#include "USimpleButton.h"
#include "UAboutProgram.h"
#include "USettings.h"
#include "UInfoEyes.h"

const int rightBorder = 12;


class UEyes: public QWidget
{
    Q_OBJECT
    
public:
    UEyes(QWidget *parent = 0);
    void createGUI();
    void createSystemTrayIcon();

    void useInfoEyes(const UInfoEyes *ie);

    bool isTopOfAllWindows();

    void setOrientation(Qt::Orientation orientation);

    void setIndentBetweenEyes(int indent);

    void setIndentTop(int indent);
    void setIndentLeft(int indent);
    void setIndentRight(int indent);
    void setIndentBottom(int indent);

    Qt::Orientation orientation();

    int indentBetweenEyes();

    int indentTop();
    int indentLeft();
    int indentRight();
    int indentBottom();

    void setOpacity(qreal opacity);
    qreal opacity();

    void setBrush(QBrush brush);
    QBrush brush();

    void setPen(QPen pen);
    QPen pen();

    QRect frame();
    bool isMouseEnter(const QPoint pos);

    int numberOfEyes();

    void setInterval(int msec);
    int interval();

    void setAutoSizeEyes(bool autoSize);
    bool autoSizeEyes();

    int diameterEyes();

private:
    QTimer timerCursorPos;

    QPoint globalPosCursor;
    QPoint oldPosition;
    bool buttonPress;

    QList <UEyeWidget *> eyes;

    Qt::Orientation d_orientation;

    int d_indentBetweenEyes;

    int d_indentTop;
    int d_indentLeft;
    int d_indentRight;
    int d_indentBottom;

    qreal d_opacity;

    QBrush d_brush;
    QPen d_pen;

    QSystemTrayIcon systemTrayIcon;
    QAction *actionAddEye;
    QAction *actionRemoveEye;
    QAction *actionSettings;
    QAction *actionQuit;
    QAction *actionAboutProgram;
    QAction *actionHorizontal;
    QAction *actionVertical;
    QAction *actionOnTop;
    QAction *actionBehind;
    QAction *actionShow;
    QAction *actionHide;
    QAction *actionShowFrame;
    QAction *actionHideFrame;

    QWidget *systemPanel;
    USimpleButton *sButtonAdd;
    USimpleButton *sButtonRemove;
    USimpleButton *sButtonSettings;
    USimpleButton *sButtonMinimize;
    USimpleButton *sButtonClose;
    USimpleButton *sButtonHorizontal;
    USimpleButton *sButtonVertical;
    USimpleButton *sButtonOnTop;
    USimpleButton *sButtonBehind;

    bool d_autoSizeEyes;    
    bool d_visibleFrame;

private:
    void drawBackground(QPainter *painter, const QRect rect, const QBrush brush,
                        qreal xRadius, qreal yRadius, const qreal opacity = 1.0,
                        const QPen pen = Qt::NoPen);
    void setSettings(USettings *settings);

public slots:
    void addEye(int number);
    void addEye();
    void setNumberEyes(int number);
    void removeEye();
    void updateMinimumSize();
    void updateSize();
    void setHorizontalOrientation();
    void setVerticalOrientation();
    void setTopOfAllWindows(bool top);
    void setOnTop();
    void setBehind();
    void settings();
    void about();    
    void setDiameterEyes(int diameter);    
    void setRadiusXIris(int radius);
    void setRadiusYIris(int radius);
    void setRadiusXPupil(int radius);
    void setRadiusYPupil(int radius);
    void setVisibleIris(bool visible);
    void setVisiblePupil(bool visible);
    void restoreDefaults();
    void setVisibleFrame(bool visible);
    void hideFrame();
    void showFrame();

private slots:
    void refreshLookThere();
    void activationReason(QSystemTrayIcon::ActivationReason reason);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void changeEvent(QEvent *event);
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);   
};

#endif // UEYES_H
