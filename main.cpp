#include "UEyes.h"
#include <QApplication>

class UTextCodec
{
public:
    static void initTextCodecs(const char *codecName)
    {
        QTextCodec *codec = QTextCodec::codecForName(codecName);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForTr(codec);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/IconProgram"));
    app.setApplicationName("WikiEyes");
    app.setApplicationVersion("0.0.1");
    app.setQuitOnLastWindowClosed(false);

    UTextCodec::initTextCodecs("utf8");

    UEyes w;
    w.setNumberEyes(2);
    w.setOrientation(Qt::Horizontal);
    w.setOpacity(0.6);
    w.setBrush(Qt::black);
    w.move(100, 100);
    w.show();
    w.showFrame();
    w.updateSize();

    return app.exec();
}
