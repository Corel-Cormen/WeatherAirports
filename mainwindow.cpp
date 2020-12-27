#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTemporaryFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString airportId = "KBVY";
    QString url = QString("https://w1.weather.gov/xml/current_obs/%1.xml").arg(airportId);

    QNetworkAccessManager *menager = new QNetworkAccessManager(this);
    connect(menager, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileIsReady(QNetworkReply*)));
    QNetworkReply *reply = menager->get(QNetworkRequest(QUrl(url)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileIsReady( QNetworkReply * reply)
{
    QFile file("myFile.xml");
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();
}
