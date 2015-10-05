#include <QPainter>
#include <QSettings>

#include "TrayIcon.h"

TrayIcon::TrayIcon(QObject *parent)
        : QSystemTrayIcon(parent)
{
    yhenda();
    suurus = QSize(100,100);
	qDebug()<<"suurus.height() = "<<suurus.height();
    font = QFont("Verdana narrow",((suurus.height()-3)/2), QFont::DemiBold);

    pmap = new QPixmap(suurus);
    drawPix();

    taimer.setInterval(1200);
    taimer.start();

    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(clicked(QSystemTrayIcon::ActivationReason)));
    connect(&taimer, SIGNAL(timeout()), this, SLOT(drawPix()));
}

void TrayIcon::clicked(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case(QSystemTrayIcon::Trigger):
        {
            drawPix();
            break;
        }
    case(QSystemTrayIcon::MiddleClick):
        {
            qApp->quit();
            break;
        }
    default:
        break;
    }
}

void TrayIcon::drawPix()
{
    QSqlQuery query;
    query.exec("SELECT temperatuur FROM temperatuur order by aeg desc limit 1;");
    if(!query.next())
    {
        db.close();
        db.open();
    } 
    qDebug()<<db.lastError().text();
    float val = query.value(0).toDouble();
    if(val>10) val = (int)val;

	
	QPainter painter(pmap);
    painter.setFont(font);
    painter.eraseRect(pmap->rect());
    painter.drawText(pmap->rect(), Qt::AlignCenter, QString::number(val));
    painter.end();
    ikoon.addPixmap(*pmap);
    setIcon(ikoon);
    qDebug()<<"meh"<<icon(); 
    showMessage(QString::number(val),QString::number(ikoon.actualSize(QSize(69,69)).width()));
}

void TrayIcon::yhenda()
{
	QSettings set("config.ini",QSettings::IniFormat);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setUserName(set.value("sql/user","logija").toString());
    db.setHostName(set.value("sql/host","localhost").toString());
    db.setDatabaseName(set.value("sql/db","ilm").toString());
    if(!db.open())
	{
		qDebug()<<"baasiga ei yhendu:"<<db.lastError().text();
		qApp->quit();
	}
}
