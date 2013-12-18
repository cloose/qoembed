#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QNetworkProxyFactory>

#include <oembedmanager.h>
#include <request.h>
#include <response.h>
using qoembed::OEmbedManager;
using qoembed::Request;
using qoembed::Response;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    manager(new OEmbedManager())
{
    ui->setupUi(this);

    connect(manager, SIGNAL(finished(qoembed::Response*)),
            SLOT(finished(qoembed::Response*)));

    QNetworkProxyFactory::setUseSystemConfiguration(true);

    manager->fetch(Request::createForUrl(QUrl("http://www.flickr.com/photos/bees/2341623661/")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::finished(qoembed::Response *response)
{
    qDebug() << response->type() << response->render();
    ui->webView->setHtml(response->render());
}
