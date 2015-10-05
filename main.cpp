#include <QApplication>

#include "TrayIcon.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    TrayIcon systemTray;
    systemTray.show();

    return app.exec();
}

