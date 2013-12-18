#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
namespace qoembed {
class OEmbedManager;
class Response;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void finished(qoembed::Response* response);
    
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    qoembed::OEmbedManager *manager;
};

#endif // MAINWINDOW_H
