#ifndef TESTWINDOW_HPP
#define TESTWINDOW_HPP

#include <QMainWindow>
#include "TestWorker.hpp"
#include <QThread>
#include <QtWidgets/QProgressDialog>

namespace Ui {
class TestWindow;
}

class TestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestWindow(BOW * bow, string pathToImages, QWidget *parent = 0);
    ~TestWindow();

private slots:
    void getData(QList<QString>);
    void tick();
    void wasCanceled();

private:
    Ui::TestWindow *ui;
    QProgressDialog  * progress;
    int processedImages = 0;
    bool * shouldStop;
};

#endif // TESTWINDOW_HPP
