#include "UEyes.h"

/// PUBLIC
UEyes::UEyes(QWidget *parent)
    : QWidget(parent),
      d_indentTop(20),
      d_indentLeft(4),
      d_indentRight(4),
      d_indentBottom(4),
      d_indentBetweenEyes(1),
      d_brush(Qt::black),
      buttonPress(false),
      d_autoSizeEyes(false),
      d_visibleFrame(false)
{        
    setOpacity(0.8);

    createGUI();
    createSystemTrayIcon();

    d_pen.setBrush(Qt::black);
    d_pen.setWidthF(1.0);


    setNumberEyes(2);
    setOrientation(Qt::Horizontal);
    setTopOfAllWindows(true);
    updateSize();

    setAttribute(Qt::WA_TranslucentBackground);


    setInterval(30);
    timerCursorPos.setParent(this);
    connect(&timerCursorPos, SIGNAL(timeout()), this, SLOT(refreshLookThere()));

    setMouseTracking(true);

    hide();

    setVisibleFrame(d_visibleFrame);
}

void UEyes::createGUI()
{
    QSize buttonSize(12, 12);

    sButtonAdd = new USimpleButton(":/IconAdd_Activate", ":/IconAdd_Deactivate");
    sButtonRemove = new USimpleButton(":/IconRemove_Activate", ":/IconRemove_Deactivate");
    sButtonSettings = new USimpleButton(":/IconSettings_Activate", ":/IconSettings_Deactivate");
    sButtonMinimize = new USimpleButton(":/IconMinimize_Activate", ":/IconMinimize_Deactivate");
    sButtonClose = new USimpleButton(":/IconClose_Activate", ":/IconClose_Deactivate");
    sButtonHorizontal = new USimpleButton(":/IconHorizontal_Activate", ":/IconHorizontal_Deactivate");
    sButtonVertical = new USimpleButton(":/IconVertical_Activate", ":/IconVertical_Deactivate");
    sButtonOnTop = new USimpleButton(":/IconBehind_Deactivate", ":/IconBehind_Deactivate");
    sButtonBehind = new USimpleButton(":/IconBehind_Activate", ":/IconBehind_Activate");


    sButtonAdd->setToolTip("Добавить глаз");
    sButtonRemove->setToolTip("Убрать глаз");
    sButtonSettings->setToolTip("Настройки");
    sButtonMinimize->setToolTip("Скрыть");
    sButtonClose->setToolTip("Закрыть");
    sButtonHorizontal->setToolTip("Горизонтальная ориентация");
    sButtonVertical->setToolTip("Вертикальная ориентация");
    sButtonOnTop->setToolTip("Поверх всех окон");
    sButtonBehind->setToolTip("Позади всех окон");


    sButtonAdd->setFixedSize(buttonSize);
    sButtonRemove->setFixedSize(buttonSize);
    sButtonSettings->setFixedSize(buttonSize);
    sButtonMinimize->setFixedSize(buttonSize);
    sButtonClose->setFixedSize(buttonSize);
    sButtonHorizontal->setFixedSize(buttonSize);
    sButtonVertical->setFixedSize(buttonSize);
    sButtonOnTop->setFixedSize(buttonSize);
    sButtonBehind->setFixedSize(buttonSize);

    QHBoxLayout *hBoxLayoutMain = new QHBoxLayout();
    hBoxLayoutMain->setContentsMargins(2, 2, 0, 0);
    setLayout(hBoxLayoutMain);


    systemPanel = new QWidget(this);

    QHBoxLayout *hBox = new QHBoxLayout();
    systemPanel->setLayout(hBox);
    hBox->setMargin(0);
    hBox->addSpacing(1);
    hBox->addWidget(sButtonAdd);
    hBox->addWidget(sButtonRemove);
    hBox->addSpacing(10);
    hBox->addWidget(sButtonHorizontal);
    hBox->addWidget(sButtonVertical);
    hBox->addWidget(sButtonSettings);
    hBox->addWidget(sButtonOnTop);
    hBox->addWidget(sButtonBehind);
    hBox->addSpacing(10);
    hBox->addStretch();
    hBox->addWidget(sButtonMinimize);
    hBox->addWidget(sButtonClose);

    systemPanel->move(2, 2);

    hBoxLayoutMain->addWidget(systemPanel, 0, Qt::AlignLeft | Qt::AlignTop);


    connect(sButtonAdd, SIGNAL(clicked()), this, SLOT(addEye()));
    connect(sButtonRemove, SIGNAL(clicked()), this, SLOT(removeEye()));
    connect(sButtonSettings, SIGNAL(clicked()), this, SLOT(settings()));
    connect(sButtonMinimize, SIGNAL(clicked()), this, SLOT(hide()));
    connect(sButtonClose, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(sButtonHorizontal, SIGNAL(clicked()), this, SLOT(setHorizontalOrientation()));
    connect(sButtonVertical, SIGNAL(clicked()), this, SLOT(setVerticalOrientation()));
    connect(sButtonOnTop, SIGNAL(clicked()), this, SLOT(setOnTop()));
    connect(sButtonBehind, SIGNAL(clicked()), this, SLOT(setBehind()));
}
void UEyes::createSystemTrayIcon()
{
    systemTrayIcon.setParent(this);
    systemTrayIcon.setIcon(QIcon(":/IconProgram"));
    connect(&systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(activationReason(QSystemTrayIcon::ActivationReason)));
    systemTrayIcon.show();

    QMenu *menu = new QMenu(this);
    QMenu *menuOrientation = new QMenu("Ориентация", menu);

    actionAddEye = new QAction(QIcon(":/IconAdd"), "Добавить глаз", this);
    actionRemoveEye = new QAction(QIcon(":/IconRemove"), "Удалить глаз", this);
    actionSettings = new QAction(QIcon(":/IconSettings"), "Настройки", this);
    actionQuit = new QAction(QIcon(":/IconQuit"), "Выход", this);
    actionAboutProgram = new QAction(QIcon(":/IconAboutProgram"), "О программе", this);

    connect(actionAddEye, SIGNAL(triggered()), this, SLOT(addEye()));
    connect(actionRemoveEye, SIGNAL(triggered()), this, SLOT(removeEye()));
    connect(actionSettings, SIGNAL(triggered()), this, SLOT(settings()));
    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionAboutProgram, SIGNAL(triggered()), this, SLOT(about()));


    actionOnTop = new QAction(QIcon(""), "Поверх всех окон", this);
    actionBehind = new QAction(QIcon(""), "Позади всех окон", this);

    actionOnTop->setCheckable(true);
    actionBehind->setCheckable(true);

    connect(actionOnTop, SIGNAL(triggered()), this, SLOT(setOnTop()));
    connect(actionBehind, SIGNAL(triggered()), this, SLOT(setBehind()));


    actionShow = new QAction(QIcon(""), "Показать", this);
    actionHide = new QAction(QIcon(""), "Скрыть", this);

    connect(actionShow, SIGNAL(triggered()), this, SLOT(show()));
    connect(actionHide, SIGNAL(triggered()), this, SLOT(hide()));


    actionShowFrame = new QAction(QIcon(""), "Показать рамку", this);
    actionHideFrame = new QAction(QIcon(""), "Скрыть рамку", this);

    actionShowFrame->setVisible(!d_visibleFrame);
    actionHideFrame->setVisible(d_visibleFrame);

    connect(actionShowFrame, SIGNAL(triggered()), this, SLOT(showFrame()));
    connect(actionHideFrame, SIGNAL(triggered()), this, SLOT(hideFrame()));


    menu->addAction(actionAddEye);
    menu->addAction(actionRemoveEye);
    menu->addSeparator();
    menu->addAction(actionShow);
    menu->addAction(actionHide);
    menu->addSeparator();
    menu->addMenu(menuOrientation);
    menu->addAction(actionSettings);
    menu->addSeparator();
    menu->addAction(actionOnTop);
    menu->addAction(actionBehind);
    menu->addSeparator();
    menu->addAction(actionShowFrame);
    menu->addAction(actionHideFrame);
    menu->addSeparator();
    menu->addAction(actionQuit);
    menu->addSeparator();
    menu->addAction(actionAboutProgram);

    actionHorizontal = new QAction(QIcon(":/IconHorizontal_Activate"), "Горизонтальная", this);
    actionVertical = new QAction(QIcon(":/IconVertical_Activate"), "Вертикальная", this);

    actionHorizontal->setCheckable(true);
    actionVertical->setCheckable(true);

    connect(actionHorizontal, SIGNAL(triggered()), this, SLOT(setHorizontalOrientation()));
    connect(actionVertical, SIGNAL(triggered()), this, SLOT(setVerticalOrientation()));

    menuOrientation->addAction(actionHorizontal);
    menuOrientation->addAction(actionVertical);

    systemTrayIcon.setContextMenu(menu);
}

void UEyes::useInfoEyes(const UInfoEyes *ie)
{
    infoEyes.infoFrom(ie);
}

bool UEyes::isTopOfAllWindows()
{ return windowFlags().testFlag(Qt::WindowStaysOnTopHint); }

void UEyes::setOrientation(Qt::Orientation orientation)
{
    d_orientation = orientation;

    bool isHorizontal = d_orientation == Qt::Horizontal;

    sButtonHorizontal->setVisible(!isHorizontal);
    sButtonVertical->setVisible(isHorizontal);

    actionHorizontal->setChecked(isHorizontal);
    actionVertical->setChecked(!isHorizontal);

    updateSize();
}

void UEyes::setIndentBetweenEyes(int indent)
{ d_indentBetweenEyes = indent; }

void UEyes::setIndentTop(int indent)
{ d_indentTop = indent; }
void UEyes::setIndentLeft(int indent)
{ d_indentLeft = indent; }
void UEyes::setIndentRight(int indent)
{ d_indentRight = indent; }
void UEyes::setIndentBottom(int indent)
{ d_indentBottom = indent; }

Qt::Orientation UEyes::orientation()
{ return d_orientation; }

int UEyes::indentBetweenEyes()
{ return d_indentBetweenEyes; }

int UEyes::indentTop()
{ return d_indentTop; }
int UEyes::indentLeft()
{ return d_indentLeft; }
int UEyes::indentRight()
{ return d_indentRight; }
int UEyes::indentBottom()
{ return d_indentBottom; }

void UEyes::setOpacity(qreal opacity)
{ d_opacity = opacity; }
qreal UEyes::opacity()
{ return d_opacity; }

void UEyes::setBrush(QBrush brush)
{ d_brush = brush; }
QBrush UEyes::brush()
{ return d_brush; }

void UEyes::setPen(QPen pen)
{ d_pen = pen; }
QPen UEyes::pen()
{ return d_pen; }

QRect UEyes::frame()
{
    if(eyes.isEmpty())
        rect();

    int width;
    int height;

    int widthEye = eyes.first()->width();
    int heightEye = eyes.first()->height();

    int sumIndent = (numberOfEyes() - 1) * d_indentBetweenEyes;

    int sumWidthEyes = numberOfEyes() * widthEye;
    int sumHeightEyes = numberOfEyes() * heightEye;

    if(d_orientation == Qt::Horizontal)
    {
        width = sumWidthEyes + d_indentLeft + d_indentRight + sumIndent;
        height = heightEye + d_indentTop + d_indentBottom;
    }else
    {
        width = widthEye + d_indentLeft + d_indentRight;
        height = sumHeightEyes + d_indentTop + d_indentBottom + sumIndent;
    }

    if(width < systemPanel->layout()->sizeHint().width())
        width = systemPanel->layout()->sizeHint().width();

    QRect rect;
    rect.setX(0);
    rect.setY(0);
    rect.setWidth(width);
    rect.setHeight(height);

    return rect;
}
bool UEyes::isMouseEnter(const QPoint pos)
{
    QRect rect = frame();
    QPoint position = mapFromGlobal(pos);

    return position.x() >= rect.x()
            && position.y() >= rect.y()
            && position.x() <= rect.width()
            && position.y() <= rect.height();
}

int UEyes::numberOfEyes()
{ return eyes.size(); }

void UEyes::setInterval(int msec)
{ timerCursorPos.setInterval(msec); }
int UEyes::interval()
{ return timerCursorPos.interval(); }

void UEyes::setAutoSizeEyes(bool autoSize)
{ d_autoSizeEyes = autoSize; }
bool UEyes::autoSizeEyes()
{ return d_autoSizeEyes; }

int UEyes::diameterEyes()
{
    if(eyes.isEmpty())
        return -1;

    return eyes.first()->width();
}

/// PRIVATE
void UEyes::drawBackground(QPainter *painter, const QRect rect, const QBrush brush,
                           qreal xRadius, qreal yRadius,
                           const qreal opacity, const QPen pen)
{
    painter->save();
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->setOpacity(opacity);
    painter->drawRoundedRect(rect, xRadius, yRadius);
    painter->restore();
}
void UEyes::setSettings(USettings *settings)
{
    settings->gui()->hSliderSizeEye->setRange(minimalWidthEye, maximalWidthEye);
    settings->gui()->hSliderSizeEye->setValue(infoEyes.diameter);

    settings->gui()->hSliderNumberEyes->setRange(minimalNumberEyes, maximalNumberEyes);
    settings->gui()->hSliderNumberEyes->setValue(infoEyes.number);

    settings->gui()->hSliderRXIris->setValue(eyes.first()->percentIrisRadiusX());
    settings->gui()->hSliderRYIris->setValue(eyes.first()->percentIrisRadiusY());
    settings->gui()->hSliderRXPupil->setValue(eyes.first()->percentPupilRadiusX());
    settings->gui()->hSliderRYPupil->setValue(eyes.first()->percentPupilRadiusY());

    connect(settings->gui()->hSliderSizeEye, SIGNAL(valueChanged(int)),
            this, SLOT(setDiameterEyes(int)));
    connect(settings->gui()->hSliderSizeEye, SIGNAL(valueChanged(int)),
            &infoEyes, SLOT(setDiameter(int)));

    connect(settings->gui()->hSliderNumberEyes, SIGNAL(valueChanged(int)),
            this, SLOT(setNumberEyes(int)));
    connect(settings->gui()->hSliderNumberEyes, SIGNAL(valueChanged(int)),
            &infoEyes, SLOT(setNumber(int)));

    connect(settings->gui()->hSliderRXIris, SIGNAL(valueChanged(int)),
            this, SLOT(setRadiusXIris(int)));
    connect(settings->gui()->hSliderRYIris, SIGNAL(valueChanged(int)),
            this, SLOT(setRadiusYIris(int)));
    connect(settings->gui()->hSliderRXPupil, SIGNAL(valueChanged(int)),
            this, SLOT(setRadiusXPupil(int)));
    connect(settings->gui()->hSliderRYPupil, SIGNAL(valueChanged(int)),
            this, SLOT(setRadiusYPupil(int)));

    connect(settings->gui()->cBoxVisibleIris, SIGNAL(clicked(bool)),
            this, SLOT(setVisibleIris(bool)));
    connect(settings->gui()->cBoxVisiblePupil, SIGNAL(clicked(bool)),
            this, SLOT(setVisiblePupil(bool)));

//    connect(settings->gui()->buttonBox->button(QDialogButtonBox::RestoreDefaults), SIGNAL(clicked()),
//            this, SLOT(restoreDefaults()));
}

/// PUBLIC SLOTS
void UEyes::addEye(int number)
{
    if(number <= 0)
        return;

    while(number != 0)
    {
        addEye();
        number--;
    }
}

void UEyes::addEye()
{    
    UEyeWidget *eye = new UEyeWidget(this);
    eye->setDiameter(infoEyes.diameter);
    eye->show();

    eyes.append(eye);

    sButtonRemove->show();

    if(numberOfEyes() == maximalNumberEyes)
        sButtonAdd->hide();

    updateSize();
}
void UEyes::setNumberEyes(int number)
{
    if(number <= 0)
        return;

    if(number == numberOfEyes())
        return;

    if(number > numberOfEyes())
    {
        while(number != numberOfEyes())
            addEye();
    }else
    {
        while(number != numberOfEyes())
            removeEye();
    }
}
void UEyes::removeEye()
{
    if(numberOfEyes() == 1)
        return;

    eyes.takeLast()->deleteLater();

    if(numberOfEyes() == minimalNumberEyes)
        sButtonRemove->hide();

    sButtonAdd->show();

    updateSize();
}

void UEyes::updateMinimumSize()
{    
    if(eyes.isEmpty())
        return;

    int minWidth;
    int minHeight;

    int widthEye = eyes.first()->width();
    int heightEye = eyes.first()->height();

    int sumIndent = (numberOfEyes() - 1) * d_indentBetweenEyes;

    int sumWidthEyes = numberOfEyes() * widthEye;
    int sumHeightEyes = numberOfEyes() * heightEye;

    if(d_orientation == Qt::Horizontal)
    {
        minWidth = sumWidthEyes + d_indentLeft + d_indentRight + sumIndent;
        minHeight = heightEye + d_indentTop + d_indentBottom;
    }else
    {
        minWidth = widthEye + d_indentLeft + d_indentRight;
        minHeight = sumHeightEyes + d_indentTop + d_indentBottom + sumIndent;
    }

    if(minWidth < systemPanel->layout()->sizeHint().width())
        minWidth = systemPanel->layout()->sizeHint().width();

    systemPanel->setFixedWidth(minWidth - d_indentRight);
    setMinimumSize(minWidth + d_indentLeft + d_indentRight,
                   minHeight + d_indentTop + d_indentBottom);
}
void UEyes::updateSize()
{
    updateMinimumSize();
    qApp->postEvent(this, new QResizeEvent(size(), size()));
}
void UEyes::setHorizontalOrientation()
{ setOrientation(Qt::Horizontal); }
void UEyes::setVerticalOrientation()
{ setOrientation(Qt::Vertical); }

void UEyes::setTopOfAllWindows(bool top)
{
    QPoint oldPos = pos();

    Qt::WindowFlags flags;

    if(top)
        flags = /*Qt::FramelessWindowHint
                | */Qt::Tool
                | Qt::WindowStaysOnTopHint;
    else
        flags = Qt::FramelessWindowHint
                | Qt::Tool
                | Qt::WindowStaysOnBottomHint;

    setWindowFlags(flags);

    showNormal();
    move(oldPos);

    sButtonOnTop->setVisible(!top);
    sButtonBehind->setVisible(top);
    actionOnTop->setChecked(top);
    actionBehind->setChecked(!top);
}
void UEyes::setOnTop()
{ setTopOfAllWindows(true); }
void UEyes::setBehind()
{ setTopOfAllWindows(false); }

void UEyes::settings()
{
    USettings *settings = new USettings(this);
    setSettings(settings);
    settings->resize(settings->layout()->sizeHint());
    settings->exec();
    settings->deleteLater();
}
void UEyes::about()
{
    UAboutProgram *aboutProgram = new UAboutProgram();
    aboutProgram->exec();
    aboutProgram->deleteLater();
}
void UEyes::setDiameterEyes(int diameter)
{
    foreach(UEyeWidget *eye, eyes)
        eye->setDiameter(diameter);

    updateSize();
}

void UEyes::setRadiusXIris(int radius)
{
    foreach(UEyeWidget *eye, eyes)
        eye->setPercentIrisRadiusX(radius);

    updateSize();
}
void UEyes::setRadiusYIris(int radius)
{
    foreach(UEyeWidget *eye, eyes)
        eye->setPercentIrisRadiusY(radius);

    updateSize();
}
void UEyes::setRadiusXPupil(int radius)
{
    foreach(UEyeWidget *eye, eyes)
        eye->setPercentPupilRadiusX(radius);

    updateSize();
}
void UEyes::setRadiusYPupil(int radius)
{
    foreach(UEyeWidget *eye, eyes)
        eye->setPercentPupilRadiusY(radius);

    updateSize();
}
void UEyes::setVisibleIris(bool visible)
{
    foreach(UEyeWidget *eye, eyes)
        eye->setVisibleIris(visible);
}
void UEyes::setVisiblePupil(bool visible)
{
    foreach(UEyeWidget *eye, eyes)
        eye->setVisiblePupil(visible);
}
void UEyes::restoreDefaults()
{
    useInfoEyes(&defaultInfoEyes);
}
void UEyes::setVisibleFrame(bool visible)
{
    d_visibleFrame = visible;
    systemPanel->setVisible(visible);
    update();
}
void UEyes::hideFrame()
{
    setVisibleFrame(false);
    actionShowFrame->setVisible(!d_visibleFrame);
    actionHideFrame->setVisible(d_visibleFrame);
}
void UEyes::showFrame()
{
    setVisibleFrame(true);
    actionShowFrame->setVisible(!d_visibleFrame);
    actionHideFrame->setVisible(d_visibleFrame);
}

/// PRIVATE SLOTS
void UEyes::refreshLookThere()
{    
    update();

    QPoint position = QCursor::pos();

    foreach(UEyeWidget *eye, eyes)
        eye->lookThere(position);
}
void UEyes::activationReason(QSystemTrayIcon::ActivationReason reason)
{    
    if(reason == QSystemTrayIcon::DoubleClick)
    {
        if(!isVisible())
            showNormal();
        else
            hide();

    }else if(reason == QSystemTrayIcon::Context)
        actionRemoveEye->setEnabled(numberOfEyes() != 1);
}

///PROTECTED
void UEyes::paintEvent(QPaintEvent *)
{
    if(!d_visibleFrame)
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    qreal xRadius = 7;
    qreal yRadius = 7;

    QRect f = frame();

    drawBackground(&painter, f, d_brush, xRadius, yRadius, d_opacity, d_pen);

    painter.save();
    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);

    int x = 0;
    int y = 0;
    int w = f.width();
    int h = systemPanel->height() + 4;

    painter.drawRoundedRect(x, y, w, h, xRadius, yRadius);
    painter.restore();
}

void UEyes::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        oldPosition = event->pos();
        buttonPress = true;
    }
}

void UEyes::mouseReleaseEvent(QMouseEvent *)
{
    buttonPress = false;
}

void UEyes::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->pos();

    QPoint delta = p - oldPosition;

    if(buttonPress)
        move(pos() + delta);
}
void UEyes::resizeEvent(QResizeEvent *event)
{
    if(eyes.isEmpty())
        return;

    int x = d_indentLeft;
    int y = d_indentTop;

    // т.к. размеры всех глаз одинаковы, то можно
    // обратиться к любому из доступных глаз, чтобы
    // взять его размер
    int w = eyes.first()->width();
    int h = eyes.first()->height();

    if(d_autoSizeEyes)
    {
        if(d_orientation == Qt::Horizontal)
        {
            w = (event->size().width() - (d_indentLeft + d_indentRight)
                 - (numberOfEyes() - 1) * d_indentBetweenEyes) / numberOfEyes();
            h = event->size().height() - (d_indentTop + d_indentBottom);
        }else
        {
            w = event->size().width() - (d_indentLeft + d_indentRight);
            h = (event->size().height() - (d_indentTop + d_indentBottom)
                 - (numberOfEyes() - 1) * d_indentBetweenEyes) / numberOfEyes();
        }
    }

    int diameter = qMin(w, h);

    foreach(UEyeWidget *eye, eyes)
    {
        eye->move(x, y);
        eye->resize(diameter,
                    diameter);

        if(d_orientation == Qt::Horizontal)
            x = eye->x() + eye->width() + d_indentBetweenEyes;
        else
            y = eye->y() + eye->height() + d_indentBetweenEyes;
    }
}

void UEyes::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::WindowStateChange)
        if(isMinimized())
            QTimer::singleShot(0, this, SLOT(hide()));
}
void UEyes::showEvent(QShowEvent *)
{
    timerCursorPos.start();
    actionShow->setVisible(false);
    actionHide->setVisible(true);
}
void UEyes::hideEvent(QHideEvent *)
{
    timerCursorPos.stop();
    actionShow->setVisible(true);
    actionHide->setVisible(false);
}

//    QRadialGradient gradient(leftEye.iris.center, 15);
//    gradient.setColorAt(0.0, QColor(216, 30, 20));
//    gradient.setColorAt(1.0, QColor(0,0,0));
//    leftEye.iris.brush = QBrush(gradient);
