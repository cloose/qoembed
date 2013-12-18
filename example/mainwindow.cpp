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
    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);

    connect(manager, SIGNAL(finished(qoembed::Response*)),
            SLOT(finished(qoembed::Response*)));

    QNetworkProxyFactory::setUseSystemConfiguration(true);
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

void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty()) {
        return;
    }

    QUrl resourceUrl(ui->lineEdit->text());
    manager->fetch(Request::createForUrl(resourceUrl));
}
