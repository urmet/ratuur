#include <QSystemTrayIcon>
#include <QtSql>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    TrayIcon(QObject *parent = 0);

private slots:
    void clicked(QSystemTrayIcon::ActivationReason reason);
    void drawPix();

private:
    void yhenda();
    QSqlDatabase db;
	QIcon ikoon;
    QPixmap *pmap;
    QSize suurus;
    QFont font;
    QTimer taimer;
};
